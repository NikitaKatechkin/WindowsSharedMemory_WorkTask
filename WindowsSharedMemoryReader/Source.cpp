#include <windows.h>
#include <iostream>
#include <fstream>

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

int main()
{
    const unsigned int BUF_SIZE = 256;
    const std::wstring SHARED_MEMORY_NAME = L"Global\\MyFileMappingObject";

    HANDLE mapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS,
                                      FALSE, 
                                      SHARED_MEMORY_NAME.c_str());
    if (mapFile != NULL)
    {
        std::wcout << L"Successfully open file mapping object." << std::endl;

        const char* viewBuffer = static_cast<const char*>(MapViewOfFile(mapFile,
                                                   FILE_MAP_ALL_ACCESS,
                                                   0,
                                                   0,
                                                   BUF_SIZE));

        if (viewBuffer != NULL)
        {
            std::wcout << L"Successfully map view of file." << std::endl;

            WriteConfig("cfg.txt", viewBuffer);

            UnmapViewOfFile(viewBuffer);
            CloseHandle(mapFile);
        }
        else
        {
            std::wcout << L"Failed to map view of file." << std::endl;
            std::wcout << L"GLE = " << GetLastError() << "." << std::endl;

            CloseHandle(mapFile);
        }
    }
    else
    {
        std::wcout << L"Failed to open file mapping object." << std::endl;
        std::wcout << L"GLE = " << GetLastError() << "." << std::endl;
    }

    system("pause");

    return 0;
}