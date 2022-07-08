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

	m_sharedMemoryView = static_cast<char*>(MapViewOfFile(m_sharedMemoryHandle,
														FILE_MAP_ALL_ACCESS,
														0,
														0,
														m_sharedMemorySize));

	if (m_sharedMemoryView == nullptr)
	{
		throw std::exception((std::string("[SharedMemoryIOHandler::SharedMemoryIOHandler()] >> ") +
							  std::string("Failed to map a shared memory handler object.")).c_str());
	}
}

SharedMemoryIOHandler::~SharedMemoryIOHandler()
{
	if (m_sharedMemoryView != nullptr)
	{
		UnmapViewOfFile(m_sharedMemoryView);
		m_sharedMemoryView = nullptr;
	}

	if (m_sharedMemoryHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_sharedMemoryHandle);
		m_sharedMemoryHandle = INVALID_HANDLE_VALUE;
	}
}

bool SharedMemoryIOHandler::Read(char* buffer, size_t bytesToRead)
{
	if (m_sharedMemoryView == nullptr || buffer == nullptr || bytesToRead <= 0)
	{
		return false;
	}
	
	memcpy_s(buffer, (bytesToRead > m_sharedMemorySize) ? m_sharedMemorySize : bytesToRead, 
			 m_sharedMemoryView, m_sharedMemorySize);

	return true;
}

bool SharedMemoryIOHandler::Write(const char* data, size_t bytesToWrite)
{
	if (m_sharedMemoryView == nullptr || data == nullptr || bytesToWrite <= 0)
	{
		return false;
	}

	memcpy_s(m_sharedMemoryView, m_sharedMemorySize, data, bytesToWrite);

	return true;
}

