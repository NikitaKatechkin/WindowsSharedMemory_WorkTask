#pragma once

#include <windows.h>
#include <iostream>

namespace SharedMemoryToolbox
{
	HANDLE AllocateSharedMemory(const std::wstring& sharedMemoryName,
								const unsigned int requiredMemorySize);
	void FreeSharedMemory(HANDLE& sharedMemory);

	void WriteToSharedMemory(const void* sharedMemoryView, const std::string& messageToWrite);

	void* MapSharedMemoryView(HANDLE sharedMemory, const unsigned int requiredMemorySize);
	void UnmapSharedMemoryView(const void* sharedMemoryView);
}