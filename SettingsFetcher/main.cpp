#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "SettingsFetcher.h"
#include "SettingsWriter.h"
#include "Memory.h"

int main(int argc, char *argv[]) {
    std::vector<DWORD> found;

    try {
        found = Memory::FindProcesses(L"Continuum.exe");
    } catch (const std::exception& e) {
        std::wcerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    if (found.size() == 0) {
        std::wcout << "No continuum processes found." << std::endl;
        return 0;
    }

    for (DWORD pid : found) {
        continuum::ClientSettings settings;

        try {
            continuum::SettingsFetcher fetcher(pid);
            settings = fetcher.GetSettings();
        } catch (continuum::FetchException& e) {
            std::wcerr << L"pid " << pid << L" error: " << e.what() << std::endl;
            continue;
        }
        
        continuum::SettingsWriter writer(settings);

        std::ofstream out(std::to_string(pid) + ".conf", std::ios::out);

        if (out.is_open())
            writer.Write(out);
    }

    return 0;
}
