#pragma once

#include <xaudio2.h>
#include <Windows.h>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <mmiscapi.h>

struct WavData {
	WAVEFORMATEX waveFormat;
	std::vector<BYTE> audioData;
};

class AudioManager
{
private:
	IXAudio2* xAudio = nullptr;
	IXAudio2MasteringVoice* masteringVoice = nullptr;

	struct AudioResource {
		WavData data;
		IXAudio2SourceVoice* sourceVoice;
	};

	std::unordered_map<std::string, std::unique_ptr<AudioResource>> wavList;
	
public:
	AudioManager() {
		// COM ��������
		HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		if (FAILED(hr)) {
			throw std::runtime_error("Failed to initialize COM. Error Code: " + std::to_string(hr));
		}
		//XAudio2��������
		if (FAILED(hr=XAudio2Create(&xAudio, 0))) {
			std::string msg = "XAudio2�𐶐����s: " + std::to_string(hr) + "\n";
			OutputDebugStringA(msg.c_str());
			throw std::runtime_error("Faied to create XAudio2" + std::to_string(hr));
		}
		if (FAILED(hr=xAudio->CreateMasteringVoice(&masteringVoice))) {
			std::string msg = "�}�X�^�����O�{�C�X�𐶐����s: " + std::to_string(hr) + "\n";
			OutputDebugStringA(msg.c_str());
			throw std::runtime_error("Failed to create mastering voice: " + std::to_string(hr));
		}
	}
	~AudioManager() {
		for (auto& [key, resource] : wavList) {
			resource->sourceVoice->DestroyVoice();
		}
		if (masteringVoice) masteringVoice->DestroyVoice();
		if (xAudio) xAudio->Release();
		// COM �����
		CoUninitialize();
	}

	//�p�X����wav��ǉ�
	void addWav(const std::string& wavName, const std::wstring& path) {
		WavData wavData = loadWavFromFile(path);
		addWavInternal(wavData, wavName);
	}
	//���\�[�X����wav��ǉ�
	void addWav(const std::string& wavName, const HINSTANCE hInstance, const int resourceId) {
		WavData wavData = loadWavFromResource(hInstance, resourceId);
		addWavInternal(wavData, wavName);
	}

	//�Đ�
	void play(const std::string& wavName, bool loop = false) {
		if (wavList.find(wavName) == wavList.end()) {
			std::string msg = "���O: " + wavName + " �̃f�[�^�͑��݂��܂���B";
			throw std::out_of_range(msg.c_str());
		}
		auto& resource = wavList.at(wavName);

		if (FAILED(resource->sourceVoice->SubmitSourceBuffer(createBuffer(resource->data, loop)))) {
			throw std::runtime_error("�\�[�X�o�b�t�@�ɒ�o���s");
		}
		if (FAILED(resource->sourceVoice->Start())) {
			throw std::runtime_error("�v���C�o�b�N���J�n���s");
		}
	}
	//��~
	void stop(const std::string& wavName) {
		if (wavList.find(wavName) == wavList.end()) {
			std::string msg = "wavName: " + wavName + " ��wavList�ɂ���܂���B";
			throw std::out_of_range(msg.c_str());
		}
		auto& resource = wavList.at(wavName);
		resource->sourceVoice->Stop();
		resource->sourceVoice->FlushSourceBuffers();
	}

private:
	//wavData���R���e�i�ɒǉ�
	void addWavInternal(const WavData& wavData, const std::string& wavName) {
		IXAudio2SourceVoice* sourceVoice = nullptr;
		HRESULT hr;
		if (FAILED(hr=xAudio->CreateSourceVoice(&sourceVoice, &wavData.waveFormat))) {
			OutputDebugString(std::to_wstring(hr).c_str());
			throw std::runtime_error("�\�[�X�{�C�X�̐����Ɏ��s���܂����B");
		}
		wavList.emplace(wavName, std::make_unique<AudioResource>(AudioResource{ wavData,sourceVoice }));
	}
	//
	WavData loadWavFromResource(HINSTANCE hInstance, int resourceId) {
		//���\�[�X��id����T��
		HRSRC hRes = FindResource(hInstance, MAKEINTRESOURCE(resourceId), L"WAVE");
		if (!hRes) throw std::runtime_error("WAV���\�[�X��������܂���ł����B");

		//���������\�[�X�̓ǂݍ���
		HGLOBAL hData = LoadResource(hInstance, hRes);
		if (!hData) throw std::runtime_error("WAV���\�[�X�����[�h�ł��܂���ł����B");

		//�ǂݍ��񂾃��\�[�X�����b�N
		LPVOID pData = LockResource(hData);

		DWORD size = SizeofResource(hInstance, hRes);

		//�f�[�^���p�[�X�����^�[��
		return parseWavData(pData, size);
	}
	WavData loadWavFromFile(const std::wstring& path) {
		HANDLE hFile = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE) throw std::runtime_error("WAV�t�@�C�����J���܂���ł���");

		DWORD fileSize = GetFileSize(hFile, NULL);
		std::vector<BYTE> fileData(fileSize);
		DWORD bytesRead;
		BOOL res = ReadFile(hFile, fileData.data(), fileSize, &bytesRead, NULL);
		CloseHandle(hFile);

		if (!res) {
			throw - 1;
		}

		return parseWavData(fileData.data(), fileSize);
	}
	WavData parseWavData(const void* data, size_t size) {
		const BYTE* byteData = reinterpret_cast<const BYTE*>(data);
		if (
			memcmp(byteData, "RIFF", 4) != 0 ||
			memcmp(byteData + 8, "WAVE", 4) != 0
			) {
			throw std::runtime_error("Invalid WAV format.");
		}

		const BYTE* fmtChunk = byteData + 12;
		while (memcmp(fmtChunk, "fmt ", 4) != 0) {
			fmtChunk += 8 + *reinterpret_cast<const DWORD*>(fmtChunk + 4);
		}

		WAVEFORMATEX waveFormat = *reinterpret_cast<const WAVEFORMATEX*>(fmtChunk + 8);

		const BYTE* dataChunk = fmtChunk + 8 + *reinterpret_cast<const DWORD*>(fmtChunk + 4);
		while (memcmp(dataChunk, "data", 4) != 0) {
			dataChunk += 8 + *reinterpret_cast<const DWORD*>(dataChunk + 4);
		}

		DWORD dataSize = *reinterpret_cast<const DWORD*>(dataChunk + 4);
		std::vector<BYTE> audioData(dataSize);
		memcpy(audioData.data(), dataChunk + 8, dataSize);

		return WavData{ waveFormat, audioData };
	}
	XAUDIO2_BUFFER* createBuffer(const WavData& wavData, bool loop) {
		auto buffer = new XAUDIO2_BUFFER();

		buffer->AudioBytes = static_cast<UINT32>(wavData.audioData.size());
		buffer->pAudioData = wavData.audioData.data();
		buffer->Flags = XAUDIO2_END_OF_STREAM;
		buffer->LoopCount = loop ? XAUDIO2_LOOP_INFINITE : 0;

		return buffer;
	}
};

