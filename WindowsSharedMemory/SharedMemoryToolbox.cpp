#include "SharedMemoryToolbox.h"

namespace SharedMemoryToolbox
{
	HANDLE AllocateSharedMemory(const std::wstring& sharedMemoryName,
								const unsigned int requiredMemorySize)
	{
		HANDLE mapFile = CreateFileMapping(INVALID_HANDLE_VALUE,
										   nullptr,
										   PAGE_READWRITE,
										   0,
										   requiredMemorySize,
										   sharedMemoryName.c_str());

		return mapFile;
	}

	void FreeSharedMemory(HANDLE& sharedMemory)
	{
		CloseHandle(sharedMemory);
	}

	void WriteToSharedMemory(const void* sharedMemoryView, const std::string& messageToWrite)
	{
		CopyMemory(const_cast<PVOID>(sharedMemoryView), 
				   messageToWrite.c_str(), 
				   (messageToWrite.length() * sizeof(char)));
	}

	void* MapSharedMemoryView(HANDLE sharedMemory, const unsigned int requiredMemorySize)
	{
		return MapViewOfFile(sharedMemory, FILE_MAP_ALL_ACCESS, 0, 0, requiredMemorySize);
	}

	void UnmapSharedMemoryView(const void* sharedMemoryView)
	{
		UnmapViewOfFile(sharedMemoryView);
	}
}