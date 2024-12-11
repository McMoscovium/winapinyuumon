#pragma once


#include <Windows.h>
#include <winternl.h>
#include <ntstatus.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ntdll.lib")

// NTSTATUS�𕶎���ɕϊ�����֐�
std::string GetNtStatusMessage(NTSTATUS status)
{
    // Dos�G���[�ɕϊ�
    DWORD dwError = RtlNtStatusToDosError(status);

    // �G���[�R�[�h�������łȂ��ꍇ
    if (dwError != 0)
    {
        // FormatMessage���g�p���ăG���[���b�Z�[�W���擾
        char buffer[512];
        FormatMessageA(
            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr, dwError, 0,
            buffer, sizeof(buffer), nullptr
        );
        return std::string(buffer);
    }
    else
    {
        return "Unknown error";
    }
}