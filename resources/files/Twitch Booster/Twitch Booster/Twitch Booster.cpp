// This code is protected by copyright laws, including the DMCA (Digital Millennium Copyright Act).
// Any reproduction, modification, or distribution without explicit authorization is prohibited and may result in legal action.
// © Maybe Ange™ Corporation. All rights reserved.

#include <iostream>
#include <windows.h>

int main() {
    LPCWSTR batFile = L"run.bat";
    DWORD fileAttr = GetFileAttributes(batFile);

    if (fileAttr == INVALID_FILE_ATTRIBUTES) {
        std::cerr << "The run.bat file was not found." << std::endl;
        return 1;
    }

    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi = { 0 };

    if (CreateProcess(batFile, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        std::cerr << "Error while executing run.bat file" << std::endl;
    }

    return 0;
}