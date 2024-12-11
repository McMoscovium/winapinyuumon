#pragma once


#include <Windows.h>
#include <winternl.h>
#include <ntstatus.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ntdll.lib")

// NTSTATUSを文字列に変換する関数
std::string GetNtStatusMessage(NTSTATUS status)
{
    // Dosエラーに変換
    DWORD dwError = RtlNtStatusToDosError(status);

    // エラーコードが無効でない場合
    if (dwError != 0)
    {
        // FormatMessageを使用してエラーメッセージを取得
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