#include <WindowsSharedMemory/SharedMemoryToolbox.h>
#include <WindowsSharedMemory/ConfigToolbox.h>

int main()
{
	const unsigned int BUF_SIZE = 256;
	const std::wstring SHARED_MEMORY_NAME = L"Global\\MyFileMappingObject";

	HANDLE mapFile = SharedMemoryToolbox::AllocateSharedMemory(SHARED_MEMORY_NAME, BUF_SIZE);

	if (mapFile != NULL)
	{
		std::wcout << L"Successfully create file mapping object." << std::endl;

		const char* viewBuffer = static_cast<const char*>(
			SharedMemoryToolbox::MapSharedMemoryView(mapFile, BUF_SIZE));

		if (viewBuffer != nullptr)
		{
			std::wcout << L"Successfully map view of file." << std::endl;

			SharedMemoryToolbox::WriteToSharedMemory(viewBuffer, 
													 ConfigToolbox::ReadConfig("cfg.txt"));
			
			system("pause");
			
			SharedMemoryToolbox::UnmapSharedMemoryView(viewBuffer);
		}
		else
		{
			std::wcout << L"Failed to map view of file." << std::endl;
			std::wcout << L"GLE = " << GetLastError() << "." << std::endl;
		}

		SharedMemoryToolbox::FreeSharedMemory(mapFile);
	}
	else
	{
		std::wcout << L"Failed to create file mapping object." << std::endl;
		std::wcout << L"GLE = " << GetLastError() << "." << std::endl;
	}

	return 0;
}