#pragma once

#include <Windows.h>
#include <iostream>
#include <fstream>
#include "cereal/archives/binary.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/vector.hpp"
#include <stdexcept>
#include <bcrypt.h>
#include <vector>
#include <string>

#include "./util.h"
#include "Game/Version.h"
#include "Skill/Skill.h"


class SaveData
{
private:
    Version version;//現在のバージョン

    char power;
    char powerFilled;
    char meet;
    char meetFilled;
    char speed;
    char speedFilled;
    Skill skill;
    int score;
    char openedStages;//解放したステージの数
    bool cheated;
public:
    SaveData(const Version& version):
        version(Version(0,0,0)),
        power(1),
        powerFilled(1),
        meet(1),
        meetFilled(1),
        speed(1),
        speedFilled(1),
        score(0),
        openedStages(1),
        cheated(false)
    {
    }
    void setPower(const char pow) {
        power = pow;
    }
    void setPowerFilled(const char powF) { powerFilled = powF; }
    void setMeet(const char m) {
        meet = m;
    }
    void setMeetFilled(const char meetF) { meetFilled = meetF; }
    void setSpeed(const char s) {
        speed = s;
    }
    void setSpeedFilled(const char spdF) { speedFilled = spdF; }
    void setSkill(const Skill& s) { skill = s; }
    void setScore(const int s) {
        score = s;
    }
    void addOpenedStages() { openedStages++; }
    void setCheated(const bool c) {
        cheated = c;
    }

    char getPower()const { return power; }
    char& getPowerRef() { return power; }
    char getPowerFilled()const { return powerFilled; }
    char& getPowerFilledRef() { return powerFilled; }
    char getMeet()const { return meet; }
    char& getMeetRef() { return meet; }
    char getMeetFilled()const { return meetFilled; }
    char& getMeetFilledRef() { return meetFilled; }
    char getSpeed()const { return speed; }
    char& getSpeedRef() { return speed; }
    char getSpeedFilled()const { return speedFilled; }
    char& getSpeedFilledRef() { return speedFilled; }
    const int getScore()const {
        return score;
    }
    int& getScoreRef() { return score; }
    char getOpenedStages()const { return openedStages; }
    const bool isCheated()const {
        return cheated;
    }
    Skill getSkill()const { return skill; }
    SaveData addScore(const int s)const {
        SaveData res = *this;
        res.setScore(this->getScore() + s);
        return res;
    }


    //初期スコアに設定
    void initScore() {
        score = 500;
        cheated = false;
    }

    //データサイズを返す
    const int size()const {
        return
            sizeof(*this);
    }

    //データをシリアル化
    std::vector<BYTE> serialize()const {
        std::ostringstream oss(std::ios::binary);
        cereal::BinaryOutputArchive archive(oss);
        archive(*this);

        const std::string& str = oss.str();
        return std::vector<BYTE>(str.begin(), str.end());
    }

    //生データ列を受け取り、メンバ変数に順番に格納していく
    void deSerialize(const std::vector<BYTE>& data, const Version& currentVersion) {
        std::istringstream iss(std::string(data.begin(), data.end()), std::ios::binary);
        cereal::BinaryInputArchive archive(iss);


        try {
            archive(*this);
            // バージョンに応じたデータ補正
            if (this->version < currentVersion) {
                if (this->version > Version(0, 0, 1)) {
                    // バージョン1以上にしかないメンバ変数を補正
                    //this->playerName = "Unknown"; // 既定値
                    //this->inventory = {};         // 空のインベントリ
                }
                if (this->version > Version(0, 0, 2)) {
                    //バージョン0.0.2以上にしかないメンバ変数を補正
                }
            }
        }
        catch (...) {
            throw std::runtime_error("Failed to deserialize SaveData: data is incomplete or corrupted.");
        }
    }

    //
    void print()const {
        std::cout << std::dec;
        std::cout << "score: " << score << std::endl;
        std::cout << "cheated: " << cheated << std::endl;
    }
    
    // cereal用serialize関数
    //
    // /////////////////////////////////////////
    // ここはSaveDataのメンバ変数を増やしたらちゃんと増やす
    // //////////////////////////////////////////
    //
    template<class Archive>
    void serialize(Archive& archive) {
        archive(version, power, powerFilled, meet, meetFilled, speed, speedFilled, skill, score, openedStages, cheated);
    }
};



class SaveDataManager {
private:
    
    const std::string filename = "save.dat";

    //暗号化
    std::vector<BYTE> encrypt(
        const std::vector<BYTE>& plainText,
        const std::vector<BYTE>& key,//キーの「素」
        const std::vector<BYTE>& iv//初期化ベクトル
    )const {
        BCRYPT_ALG_HANDLE hAlgorithm;//暗号化アルゴリズムのハンドル
        BCRYPT_KEY_HANDLE hKey;//暗号化用鍵のハンドル
        DWORD dataSize, encryptedSize;//データサイズ
        std::vector<BYTE> encryptedData;//暗号化後データ

        std::vector<BYTE> copyIV = iv;


        //AESアルゴリズムを開く
        //開いたアルゴリズムは閉じる必要がある
        if (BCryptOpenAlgorithmProvider(
            &hAlgorithm,//アルゴリズムを受け取るハンドル
            BCRYPT_AES_ALGORITHM,//要求するアルゴリズム
            NULL,//特定のプロバイダを要求しない
            0//関数の動作を変更しない
        ) != 0) {
            throw std::runtime_error("Failed to open AES algorithm.");
        }

        //CBCモードに設定
        if (BCryptSetProperty(
            hAlgorithm,//設定するCNGオブジェクトへのハンドル
            BCRYPT_CHAINING_MODE,//設定するプロパティの名前
            (PBYTE)BCRYPT_CHAIN_MODE_CBC,//CBCモードのプロパティ値を含むバッファのアドレス
            sizeof(BCRYPT_CHAIN_MODE_CBC),
            0//この関数にはフラグはない
        ) != 0) {
            BCryptCloseAlgorithmProvider(hAlgorithm, 0);//アルゴリズムプロバイダを閉じる
            throw std::runtime_error("Failed to set cipher mode.");
        }

        //キーの生成
        //生成したキーは最後にdestroyする必要がある
        if (BCryptGenerateSymmetricKey(
            hAlgorithm,
            &hKey,
            nullptr,//キーオブジェクトは受け取らない
            0,//nullptrのサイズ
            (PBYTE)key.data(),//キーオブジェクトの作成元
            (ULONG)key.size(),//keyのサイズ
            0//フラグなし
        ) != 0) {
            BCryptCloseAlgorithmProvider(hAlgorithm, 0);
            throw std::runtime_error("Failed to generate key.");
        }

        //データの暗号化後サイズの計算
        if (BCryptEncrypt(
            hKey,//暗号化に使用するキー
            (PBYTE)plainText.data(),//暗号化するバッファのアドレス
            (ULONG)plainText.size(),//暗号化するバッファのサイズ
            nullptr,//埋め込み情報はなし
            (PBYTE)copyIV.data(),//初期化ベクトルのアドレス
            (ULONG)copyIV.size(),//初期化ベクトルのサイズ
            nullptr,//暗号化により生成されるテキストのを受け取る場所（今は計算だけなので受け取らない）
            0,//上のバッファのサイズ（もちろん０）
            &dataSize,//pbOutputにコピーされたバイト数を受け取る変数
            BCRYPT_BLOCK_PADDING//????????
        ) != 0) {
            BCryptDestroyKey(hKey);
            BCryptCloseAlgorithmProvider(hAlgorithm, 0);
            throw std::runtime_error("Failed to calculate encrypted data size.");
        }

        copyIV = iv;

        //データの暗号化
        encryptedData.resize(dataSize);
        if (BCryptEncrypt(
            hKey, 
            (PBYTE)plainText.data(),
            (ULONG)plainText.size(),
            nullptr, 
            (PUCHAR)copyIV.data(), 
            (ULONG)copyIV.size(),
            encryptedData.data(),//データを受け取る
            dataSize,//先ほど計算したデータサイズ
            &encryptedSize, 
            BCRYPT_BLOCK_PADDING
        ) != 0) {
            BCryptDestroyKey(hKey);
            BCryptCloseAlgorithmProvider(hAlgorithm, 0);
            throw std::runtime_error("Failed to encrypt data.");
        }

        //そうじ
        BCryptDestroyKey(hKey);
        BCryptCloseAlgorithmProvider(hAlgorithm, 0);

        return encryptedData;//完成したデータ
    }

    //復号
    std::vector<BYTE> decrypt(
        const std::vector<BYTE>& cipherText,
        const std::vector<BYTE>& key,
        const std::vector<BYTE>& iv
    )const {
        BCRYPT_ALG_HANDLE hAlgorithm;
        BCRYPT_KEY_HANDLE hKey;
        DWORD dataSize, decryptedSize;
        std::vector<BYTE> decryptedData;//復号後のデータを格納

        NTSTATUS er;

        //AESアルゴリズムを開く
        if (er=BCryptOpenAlgorithmProvider(
            &hAlgorithm,
            BCRYPT_AES_ALGORITHM,
            nullptr,
            0
        ) != 0) {
            std::string msg = GetNtStatusMessage(er);
            std::cout << msg;
            throw std::runtime_error("Failed to open AES algorithm.");
        }

        //CBCモードに設定
        if (er=BCryptSetProperty(
            hAlgorithm,
            BCRYPT_CHAINING_MODE,
            (PBYTE)BCRYPT_CHAIN_MODE_CBC,
            sizeof(BCRYPT_CHAIN_MODE_CBC),
            0
        ) != 0) {
            BCryptCloseAlgorithmProvider(hAlgorithm, 0);
            std::string msg = GetNtStatusMessage(er);
            std::cout << msg;
            throw std::runtime_error("Failed to set cipher mode.");
        }

        //キーの生成
        if (er=BCryptGenerateSymmetricKey(
            hAlgorithm,
            &hKey, 
            nullptr,
            0,
            (PBYTE)key.data(),
            (ULONG)key.size(),
            0
        ) != 0) {
            BCryptCloseAlgorithmProvider(hAlgorithm, 0);
            std::string msg = GetNtStatusMessage(er);
            std::cout << msg;
            throw std::runtime_error("Failed to generate key.");
        }

        //復号後データサイズを計算
        if (er=BCryptDecrypt(
            hKey,
            (PBYTE)cipherText.data(),
            (ULONG)cipherText.size(),
            nullptr, 
            (PBYTE)iv.data(),
            (ULONG)iv.size(), 
            nullptr,
            0,
            &dataSize,
            BCRYPT_BLOCK_PADDING
        ) != 0) {
            BCryptDestroyKey(hKey);
            BCryptCloseAlgorithmProvider(hAlgorithm, 0);
            std::string msg = GetNtStatusMessage(er);
            std::cout << msg;
            throw std::runtime_error("Failed to calculate decrypted data size.");
        }

        //復号
        decryptedData.resize(dataSize);
        if (er=BCryptDecrypt(
            hKey,
            (PBYTE)cipherText.data(), 
            (ULONG)cipherText.size(), 
            nullptr,
            (PBYTE)iv.data(), 
            (ULONG)iv.size(),
            decryptedData.data(),
            dataSize,
            &decryptedSize,
            BCRYPT_BLOCK_PADDING
        ) != 0) {
            BCryptDestroyKey(hKey);
            BCryptCloseAlgorithmProvider(hAlgorithm, 0);
            std::string msg = GetNtStatusMessage(er);
            std::cout << msg;
            std::cout << decryptedData.data() << std::endl;
            throw std::runtime_error("Failed to decrypt data.");
        }

        //そうじ
        BCryptDestroyKey(hKey);
        BCryptCloseAlgorithmProvider(hAlgorithm, 0);

        return decryptedData;
    }

public:
    SaveDataManager(){}

    //データを外部ファイルに出力
    void save(const SaveData& saveData) const {
        //キーとIV（初期化ベクトル）を生成
        std::vector<BYTE> key(16, 0x5A);//キーの例（秘密にする必要がある）
        std::vector<BYTE> iv(16, 0x00);//IVの例（各セーブにおいてランダムである必要がある）


        //データを取得
        const std::vector<BYTE> data = saveData.serialize();

        

        //plainTextの内容を出力
        std::cout << "plainText: ";
        for (BYTE b : data) {
            std::cout << "0x" << std::hex << static_cast<int>(b) << " "; // 16進数で表示
        }
        std::cout << std::endl;



        //データを暗号化
        const std::vector<BYTE> cipherText = encrypt(data, key, iv);


        //IVと暗号化後テキストをファイルに書き込む
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            throw std::runtime_error("Failed to open file for saving.");
        }

        
        outFile.write(reinterpret_cast<const char*>(iv.data()), iv.size());//iv書き込み
        outFile.write(reinterpret_cast<const char*>(cipherText.data()), cipherText.size());//データ書き込み

        //書き込み終了
        outFile.close();
    }

    //外部ファイルを読み込み、SaveDataに書き込む
    void load(SaveData& saveData, const Version& currentVersion) {
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile) {
            //ファイルがなくて読み込めない
            std::cout << "ファイルが見つかりません" << std::endl;
            saveData.initScore();
            save(saveData);
            return;
        }

        //IV読み込み
        std::vector<BYTE> iv(16);
        inFile.read(reinterpret_cast<char*>(iv.data()), iv.size());


        const std::vector<BYTE> cipherText = std::vector<BYTE>(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>());

        //復号
        const std::vector<BYTE> key(16, 0x5A);//キーの例
        const std::vector<BYTE> plainText = decrypt(cipherText, key, iv);

        //復号したデータをパースしメンバ変数に設定
        saveData.deSerialize(plainText, currentVersion);
    }
};
