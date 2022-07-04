#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace ConfigToolbox
{
    void WriteConfig(std::string configFile, const char* data);
    std::string ReadConfig(std::string configFile);
}