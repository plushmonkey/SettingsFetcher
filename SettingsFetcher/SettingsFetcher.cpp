#include "SettingsFetcher.h"
#include "Memory.h"

namespace continuum {

SettingsFetcher::SettingsFetcher(DWORD pid) 
    : m_Pid(pid), m_ProcessHandle(nullptr), m_BaseAddr(0)
{
    Initialize();
}

SettingsFetcher::~SettingsFetcher() {
    CloseHandle(m_ProcessHandle);
}

void SettingsFetcher::Initialize() {
    if (!Memory::GetDebugPrivileges())
        throw FetchException("Couldn't get debug privileges. Run as admin.");

    if (!(m_ProcessHandle = OpenProcess(PROCESS_VM_READ, FALSE, m_Pid)))
        throw FetchException("Couldn't open process.");

    if (!(m_BaseAddr = Memory::GetModuleBase(L"Continuum.exe", m_Pid)))
        throw FetchException("Couldn't get base address.");
}

ClientSettings SettingsFetcher::GetSettings() {
    uintptr_t addr = Memory::GetU32(m_ProcessHandle, m_BaseAddr + 0xC1AFC);
    addr += 0x127EC + 0x1AE70;

    ClientSettings settings;

    Memory::Read(m_ProcessHandle, addr, &settings, sizeof(ClientSettings));

    return settings;
}

}
