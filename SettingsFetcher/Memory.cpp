#include "Memory.h"

#include <tlhelp32.h>
#include <iostream>

namespace Memory {

bool GetDebugPrivileges() {
    HANDLE token = nullptr;
    bool success = false;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token)) {
        TOKEN_PRIVILEGES privileges;

        LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &privileges.Privileges[0].Luid);
        privileges.PrivilegeCount = 1;
        privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        if (AdjustTokenPrivileges(token, FALSE, &privileges, sizeof(TOKEN_PRIVILEGES), 0, 0)) {
            DWORD lastError = GetLastError();
            success = GetLastError() == ERROR_SUCCESS;
        }
        CloseHandle(token);
    }

    return success;
}

std::vector<WritableArea> GetWritableAreas(HANDLE handle) {
    MEMORY_BASIC_INFORMATION meminfo;
    DWORD pos = 0;
    const int Writable = (PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
    std::vector<WritableArea> areas;

    while (VirtualQueryEx(handle, (LPVOID)pos, &meminfo, sizeof(meminfo))) {
        if ((meminfo.Protect & Writable))
            areas.push_back(WritableArea(reinterpret_cast<unsigned int>(meminfo.BaseAddress), static_cast<unsigned int>(meminfo.RegionSize)));
        pos += meminfo.RegionSize;
    }

    return areas;
}

std::vector<unsigned int> FindU32(HANDLE handle, const unsigned int value) {
    std::vector<unsigned int> found;

    std::vector<WritableArea> areas = GetWritableAreas(handle);

    for (WritableArea& area : areas) {
        if (area.size == 0) continue;

        char *buffer = new char[area.size];
        SIZE_T num_read;

        if (ReadProcessMemory(handle, (LPVOID)area.base, buffer, area.size, &num_read)) {
            for (unsigned int i = 0; i < num_read - 4; i += 4) {
                unsigned int check = *reinterpret_cast<unsigned int *>(buffer + i);

                if (check == value)
                    found.push_back(area.base + i);
            }
        }

        delete[] buffer;
    }

    return found;
}

std::vector<unsigned int> FindRange(HANDLE handle, const unsigned int start, const unsigned int end) {
    std::vector<unsigned int> found;

    std::vector<WritableArea> areas = GetWritableAreas(handle);

    for (WritableArea& area : areas) {
        if (area.size == 0) continue;

        char *buffer = new char[area.size];
        SIZE_T num_read;

        if (ReadProcessMemory(handle, (LPVOID)area.base, buffer, area.size, &num_read)) {
            for (unsigned int i = 0; i < num_read - 4; i += 4) {
                unsigned int check = *reinterpret_cast<unsigned int *>(buffer + i);

                if (check >= start && check <= end)
                    found.push_back(area.base + i);
            }
        }

        delete[] buffer;
    }

    return found;
}

std::vector<DWORD> FindProcesses(const std::wstring& find) {
    HANDLE snapshot;

    if ((snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE)
        throw std::runtime_error("Could not create snapshot of processes.");

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(snapshot, &entry)) {
        CloseHandle(snapshot);
        throw std::runtime_error("Could not get information about process.");
    }

    std::vector<DWORD> found;

    do {
        if (_tcscmp(find.data(), entry.szExeFile) == 0)
            found.push_back(entry.th32ProcessID);
    } while (Process32Next(snapshot, &entry));

    CloseHandle(snapshot);

    return found;
}

bool Read(HANDLE handle, const uintptr_t addr, void* buffer, size_t size) {
    SIZE_T num_read;

    if (ReadProcessMemory(handle, (LPVOID)addr, buffer, size, &num_read))
        return true;
    return false;
}

unsigned int GetU32(HANDLE handle, const unsigned int address) {
    unsigned int value;
    SIZE_T num_read;

    if (ReadProcessMemory(handle, (LPVOID)address, &value, sizeof(unsigned int), &num_read))
        return value;

    return 0;
}

std::string GetString(HANDLE handle, const unsigned int address, size_t len) {
    std::string value;
    SIZE_T read;

    value.resize(len);

    if (ReadProcessMemory(handle, (LPVOID)address, const_cast<char*>(value.c_str()), len, &read))
        return value;

    return "";
}

ULONG GetModuleBase(TCHAR *name, ULONG pid) {
    MODULEENTRY32 me = { 0 };
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);

    me.dwSize = sizeof(me);
    if (snap == INVALID_HANDLE_VALUE) return 0;

    BOOL bModule = Module32First(snap, &me);
    while (bModule) {
        
        if (!name || _tcscmp(name, me.szModule) == 0) {
            CloseHandle(snap);
            return (ULONG)me.modBaseAddr;
        }
        bModule = Module32Next(snap, &me);
    }
    CloseHandle(snap);
    return 0;
}

}
