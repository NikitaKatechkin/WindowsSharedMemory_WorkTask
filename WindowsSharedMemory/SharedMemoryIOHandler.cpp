#include "SharedMemoryIOHandler.h"

SharedMemoryIOHandler::SharedMemoryIOHandler(const std::string& resourcePath, const size_t sharedMemorySize):
	BasicIOHandler(resourcePath), m_sharedMemorySize(sharedMemorySize)
{
	using converter = std::wstring_convert<std::codecvt_utf8<wchar_t>>;
	std::wstring convertedResourcePath = converter().from_bytes(m_resourcePath);

	m_sharedMemoryHandle = CreateFileMapping(INVALID_HANDLE_VALUE,
											 nullptr,
											 PAGE_READWRITE,
											 0,
											 static_cast<DWORD>(m_sharedMemorySize),
											 convertedResourcePath.c_str());

	if (m_sharedMemoryHandle == NULL)
	{
		throw std::exception((std::string("[SharedMemoryIOHandler::SharedMemoryIOHandler()] >> ") +
							  std::string("Failed to create a shared memory handler object.")).c_str());
	}
}

SharedMemoryIOHandler::~SharedMemoryIOHandler()
{
	if (m_sharedMemoryHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_sharedMemoryHandle);
		m_sharedMemoryHandle = INVALID_HANDLE_VALUE;
	}
}

bool SharedMemoryIOHandler::Read(char* buffer, size_t bytesToRead)
{
	bytesToRead = (bytesToRead > m_sharedMemorySize) ? m_sharedMemorySize : bytesToRead;

	const char* sharedMemoryView = static_cast<const char*>(MapViewOfFile(m_sharedMemoryHandle,
																		  FILE_MAP_ALL_ACCESS, 
																		  0, 
																		  0, 
																		  m_sharedMemorySize));

	bool isSuccess = (sharedMemoryView != nullptr);

	if (isSuccess == true)
	{
		memcpy_s(buffer, bytesToRead, sharedMemoryView, m_sharedMemorySize);
		UnmapViewOfFile(sharedMemoryView);
	}

	return isSuccess;
}

bool SharedMemoryIOHandler::Write(const char* data, size_t bytesToWrite)
{
	const char* sharedMemoryView = static_cast<const char*>(MapViewOfFile(m_sharedMemoryHandle,
																		  FILE_MAP_ALL_ACCESS,
																		  0,
																		  0,
																		  m_sharedMemorySize));

	bool isSuccess = ((sharedMemoryView != nullptr) && (bytesToWrite <= m_sharedMemorySize));

	if (isSuccess == true)
	{
		if (data != nullptr)
		{
			memcpy_s(const_cast<char*>(sharedMemoryView), m_sharedMemorySize, data, bytesToWrite);
		}

		UnmapViewOfFile(sharedMemoryView);
	}

	return isSuccess;
}

