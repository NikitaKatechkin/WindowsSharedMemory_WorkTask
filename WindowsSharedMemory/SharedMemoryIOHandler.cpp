#include "SharedMemoryIOHandler.h"

SharedMemoryIOHandler::SharedMemoryIOHandler(const std::string& resourcePath):
	BasicIOHandler(resourcePath)
{
	if (Open() == false)
	{
		throw std::exception();
	}
}

SharedMemoryIOHandler::~SharedMemoryIOHandler()
{
	Close();
}

bool SharedMemoryIOHandler::Read(std::string& buffer)
{
	const char* sharedMemoryView = static_cast<const char*>(MapViewOfFile(m_sharedMemoryHandle,
																		  FILE_MAP_ALL_ACCESS, 
																		  0, 
																		  0, 
																		  256));

	bool isSuccess = (sharedMemoryView != nullptr);

	if (isSuccess == true)
	{
		buffer += sharedMemoryView;
		UnmapViewOfFile(sharedMemoryView);
	}

	return isSuccess;
}

bool SharedMemoryIOHandler::Write(const char* data)
{
	const char* sharedMemoryView = static_cast<const char*>(MapViewOfFile(m_sharedMemoryHandle,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		256));

	bool isSuccess = (sharedMemoryView != nullptr);

	if (isSuccess == true)
	{
		if (data != nullptr)
		{
			CopyMemory(const_cast<PVOID>(static_cast<const void*>(sharedMemoryView)),
				data,
				(strlen(data) * sizeof(char)));
		}

		UnmapViewOfFile(sharedMemoryView);
	}

	return isSuccess;
}

bool SharedMemoryIOHandler::Open()
{
	m_sharedMemoryHandle = CreateFileMapping(INVALID_HANDLE_VALUE,
		nullptr,
		PAGE_READWRITE,
		0,
		256,
		std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(m_resourcePath).c_str());

	return (m_sharedMemoryHandle != NULL);
}

void SharedMemoryIOHandler::Close()
{
	CloseHandle(m_sharedMemoryHandle);
}
