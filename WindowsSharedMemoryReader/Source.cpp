#include <WindowsSharedMemory/SharedMemoryToolbox.h>
#include <WindowsSharedMemory/ConfigToolbox.h>

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

        const char* viewBuffer = static_cast<const char*>(
            SharedMemoryToolbox::MapSharedMemoryView(mapFile, BUF_SIZE));

        if (viewBuffer != nullptr)
        {
            std::wcout << L"Successfully map view of file." << std::endl;

            ConfigToolbox::WriteConfig("cfg.txt", viewBuffer);

            SharedMemoryToolbox::UnmapSharedMemoryView(viewBuffer);
        }
        else
        {
            std::wcout << L"Failed to map view of file." << std::endl;
            std::wcout << L"GLE = " << GetLastError() << "." << std::endl;
        }

        CloseHandle(mapFile);
    }
    else
    {
        std::wcout << L"Failed to open file mapping object." << std::endl;
        std::wcout << L"GLE = " << GetLastError() << "." << std::endl;
    }

    system("pause");

    return 0;
}