#pragma once

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <bcrypt.h>
#include <vector>

#include "./util.h"

class SaveData
{
private:
    int score;
    bool cheated;
public:
    void setScore(const int s) {
        score = s;
    }
    void setCheated(const bool c) {
        cheated = c;
    }


    //�����X�R�A�ɐݒ�
    void initScore() {
        score = 500;
        cheated = false;
    }

    //�f�[�^�T�C�Y��Ԃ�
    const int size()const {
        return sizeof(score) + sizeof(cheated);
    }

    //�f�[�^���V���A����
    const std::vector<BYTE> plainData()const {
        std::vector<BYTE> plainData(size());

        int it = 0;

        std::memcpy(plainData.data()+it, &score, sizeof(score));
        it += sizeof(score);
        std::memcpy(plainData.data()+it, &cheated, sizeof(cheated));
        it += sizeof(cheated);

        return plainData;
    }

    //���f�[�^����󂯎��A�����o�ϐ��ɏ��ԂɊi�[���Ă���
    void deSerialize(const std::vector<BYTE>& plainText) {
        if (plainText.size() < size()) {
            std::cout << "plainText.size()=: " << plainText.size() << std::endl;
            throw std::runtime_error("Invalid plainText.");
        }

        int it = 0;

        std::memcpy(&score, plainText.data() + it, sizeof(score));
        it += sizeof(score);

        std::memcpy(&cheated, plainText.data() + it, sizeof(cheated));
        it += sizeof(cheated);
    }

    //
    void print()const {
        std::cout << std::dec;
        std::cout << "score: " << score << std::endl;
        std::cout << "cheated: " << cheated << std::endl;
    }
};



class SaveDataManager {
private:
    
    const std::string filename = "save.dat";

    //�Í���
    std::vector<BYTE> encrypt(
        const std::vector<BYTE>& plainText,
        const std::vector<BYTE>& key,//�L�[�́u�f�v
        const std::vector<BYTE>& iv//�������x�N�g��
    )const {
        BCRYPT_ALG_HANDLE hAlgorithm;//�Í����A���S���Y���̃n���h��
        BCRYPT_KEY_HANDLE hKey;//�Í����p���̃n���h��
        DWORD dataSize, encryptedSize;//�f�[�^�T�C�Y
        std::vector<BYTE> encryptedData;//�Í�����f�[�^

        std::vector<BYTE> copyIV = iv;


        //AES�A���S���Y�����J��
        //�J�����A���S���Y���͕���K�v������
        if (BCryptOpenAlgorithmProvider(
            &hAlgorithm,//�A���S���Y�����󂯎��n���h��
            BCRYPT_AES_ALGORITHM,//�v������A���S���Y��
            NULL,//����̃v���o�C�_��v�����Ȃ�
            0//�֐��̓����ύX���Ȃ�
        ) != 0) {
            throw std::runtime_error("Failed to open AES algorithm.");
        }

        //CBC���[�h�ɐݒ�
        if (BCryptSetProperty(
            hAlgorithm,//�ݒ肷��CNG�I�u�W�F�N�g�ւ̃n���h��
            BCRYPT_CHAINING_MODE,//�ݒ肷��v���p�e�B�̖��O
            (PBYTE)BCRYPT_CHAIN_MODE_CBC,//CBC���[�h�̃v���p�e�B�l���܂ރo�b�t�@�̃A�h���X
            sizeof(BCRYPT_CHAIN_MODE_CBC),
            0//���̊֐��ɂ̓t���O�͂Ȃ�
        ) != 0) {
            BCryptCloseAlgorithmProvider(hAlgorithm, 0);//�A���S���Y���v���o�C�_�����
            throw std::runtime_error("Failed to set cipher mode.");
        }

        //�L�[�̐���
        //���������L�[�͍Ō��destroy����K�v������
        if (BCryptGenerateSymmetricKey(
            hAlgorithm,
            &hKey,
            nullptr,//�L�[�I�u�W�F�N�g�͎󂯎��Ȃ�
            0,//nullptr�̃T�C�Y
            (PBYTE)key.data(),//�L�[�I�u�W�F�N�g�̍쐬��
            (ULONG)key.size(),//key�̃T�C�Y
            0//�t���O�Ȃ�
        ) != 0) {
            BCryptCloseAlgorithmProvider(hAlgorithm, 0);
            throw std::runtime_error("Failed to generate key.");
        }

        //�f�[�^�̈Í�����T�C�Y�̌v�Z
        if (BCryptEncrypt(
            hKey,//�Í����Ɏg�p����L�[
            (PBYTE)plainText.data(),//�Í�������o�b�t�@�̃A�h���X
            (ULONG)plainText.size(),//�Í�������o�b�t�@�̃T�C�Y
            nullptr,//���ߍ��ݏ��͂Ȃ�
            (PBYTE)copyIV.data(),//�������x�N�g���̃A�h���X
            (ULONG)copyIV.size(),//�������x�N�g���̃T�C�Y
            nullptr,//�Í����ɂ�萶�������e�L�X�g�̂��󂯎��ꏊ�i���͌v�Z�����Ȃ̂Ŏ󂯎��Ȃ��j
            0,//��̃o�b�t�@�̃T�C�Y�i�������O�j
            &dataSize,//pbOutput�ɃR�s�[���ꂽ�o�C�g�����󂯎��ϐ�
            BCRYPT_BLOCK_PADDING//????????
        ) != 0) {
            BCryptDestroyKey(hKey);
            BCryptCloseAlgorithmProvider(hAlgorithm, 0);
            throw std::runtime_error("Failed to calculate encrypted data size.");
        }

        copyIV = iv;

        //�f�[�^�̈Í���
        encryptedData.resize(dataSize);
        if (BCryptEncrypt(
            hKey, 
            (PBYTE)plainText.data(),
            (ULONG)plainText.size(),
            nullptr, 
            (PUCHAR)copyIV.data(), 
            (ULONG)copyIV.size(),
            encryptedData.data(),//�f�[�^���󂯎��
            dataSize,//��قǌv�Z�����f�[�^�T�C�Y
            &encryptedSize, 
            BCRYPT_BLOCK_PADDING
        ) != 0) {
            BCryptDestroyKey(hKey);
            BCryptCloseAlgorithmProvider(hAlgorithm, 0);
            throw std::runtime_error("Failed to encrypt data.");
        }

        //������
        BCryptDestroyKey(hKey);
        BCryptCloseAlgorithmProvider(hAlgorithm, 0);

        return encryptedData;//���������f�[�^
    }

    //����
    std::vector<BYTE> decrypt(
        const std::vector<BYTE>& cipherText,
        const std::vector<BYTE>& key,
        const std::vector<BYTE>& iv
    )const {
        BCRYPT_ALG_HANDLE hAlgorithm;
        BCRYPT_KEY_HANDLE hKey;
        DWORD dataSize, decryptedSize;
        std::vector<BYTE> decryptedData;//������̃f�[�^���i�[

        NTSTATUS er;

        //AES�A���S���Y�����J��
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

        //CBC���[�h�ɐݒ�
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

        //�L�[�̐���
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

        //������f�[�^�T�C�Y���v�Z
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

        //����
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

        //������
        BCryptDestroyKey(hKey);
        BCryptCloseAlgorithmProvider(hAlgorithm, 0);

        return decryptedData;
    }

public:
    SaveDataManager(){}

    //�f�[�^���O���t�@�C���ɏo��
    void save(const SaveData& saveData) const {
        //�L�[��IV�i�������x�N�g���j�𐶐�
        std::vector<BYTE> key(16, 0x5A);//�L�[�̗�i�閧�ɂ���K�v������j
        std::vector<BYTE> iv(16, 0x00);//IV�̗�i�e�Z�[�u�ɂ����ă����_���ł���K�v������j


        //�f�[�^���擾
        const std::vector<BYTE>& data = saveData.plainData();

        

        //plainText�̓��e���o��
        std::cout << "plainText: ";
        for (BYTE b : data) {
            std::cout << "0x" << std::hex << static_cast<int>(b) << " "; // 16�i���ŕ\��
        }
        std::cout << std::endl;



        //�f�[�^���Í���
        const std::vector<BYTE> cipherText = encrypt(data, key, iv);


        //IV�ƈÍ�����e�L�X�g���t�@�C���ɏ�������
        std::ofstream outFile(filename, std::ios::binary);
        if (!outFile) {
            throw std::runtime_error("Failed to open file for saving.");
        }

        
        outFile.write(reinterpret_cast<const char*>(iv.data()), iv.size());//iv��������
        outFile.write(reinterpret_cast<const char*>(cipherText.data()), cipherText.size());//�f�[�^��������

        //�������ݏI��
        outFile.close();
    }

    //�O���t�@�C����ǂݍ��݁ASaveData�ɏ�������
    void load(SaveData& saveData) {
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile) {
            //�t�@�C�����Ȃ��ēǂݍ��߂Ȃ�
            std::cout << "�t�@�C����������܂���" << std::endl;
            saveData.initScore();
            save(saveData);
            return;
        }

        //IV�ǂݍ���
        std::vector<BYTE> iv(16);
        inFile.read(reinterpret_cast<char*>(iv.data()), iv.size());


        const std::vector<BYTE> cipherText = std::vector<BYTE>(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>());

        //����
        const std::vector<BYTE> key(16, 0x5A);//�L�[�̗�
        const std::vector<BYTE> plainText = decrypt(cipherText, key, iv);

        //���������f�[�^���p�[�X�������o�ϐ��ɐݒ�
        saveData.deSerialize(plainText);
    }
};
