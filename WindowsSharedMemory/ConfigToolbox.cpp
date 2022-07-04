#include "ConfigToolbox.h"

namespace ConfigToolbox
{
    void WriteConfig(std::string configFile, const char* data)
    {
        std::ofstream config_file(configFile);
        if (config_file.is_open() == true)
        {
            for (int char_index = 0; char_index < strlen(data); char_index++)
            {
                config_file << static_cast<char>(data[char_index]);
                std::cout << static_cast<char>(data[char_index]);
            }
        }
        else
        {
            std::wcout << L"Failed to open config file." << std::endl;
        }
        config_file.close();
    }

    std::string ReadConfig(std::string configFile)
    {
        std::string result;
        std::string line;

        std::ifstream myfile("cfg.txt");
        if (myfile.is_open())
        {
            while (std::getline(myfile, line))
            {
                std::cout << line << std::endl;
                result += (line + "\n");
            }
        }
        myfile.close();

        return result;
    }
}