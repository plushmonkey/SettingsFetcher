#ifndef SETTINGS_FETCHER_H_
#define SETTINGS_FETCHER_H_

#include <stdexcept>
#include <Windows.h>
#include <tchar.h>
#include "ClientSettings.h"

namespace continuum {

class FetchException : public std::exception {
public:
    FetchException(const std::string& error)
        : std::exception(error.data())
    {

    }
};

class SettingsFetcher {
private:
    HANDLE m_ProcessHandle;
    DWORD m_BaseAddr;
    DWORD m_Pid;

    void Initialize();

public:
    SettingsFetcher(DWORD pid);
    ~SettingsFetcher();

    ClientSettings GetSettings();
};

}

#endif
