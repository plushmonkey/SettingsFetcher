#ifndef SETTINGS_WRITER_H_
#define SETTINGS_WRITER_H_

#include <iosfwd>
#include "ClientSettings.h"

namespace continuum {

class SettingsWriter {
private:
    ClientSettings m_Settings;

    void WriteShipSettings(std::ostream& out, int ship);
    void WriteSpawnSettings(std::ostream& out, int freq);

public:
    SettingsWriter(const ClientSettings& settings);

    void Write(std::ostream& out);
};

}

#endif
