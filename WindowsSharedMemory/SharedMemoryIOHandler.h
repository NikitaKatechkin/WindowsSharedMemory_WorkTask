#pragma once

#include <windows.h>
#include <codecvt>
#include <locale>
#include "BasicIOHandler.h"

class SharedMemoryIOHandler final : public BasicIOHandler
{
public:
	SharedMemoryIOHandler(const std::string& resourcePath, const size_t sharedMemorySize = 256);
	virtual ~SharedMemoryIOHandler();

	virtual bool Read(char* buffer, size_t byteToRead) override;
	virtual bool Write(const char* data, size_t bytesToWrite) override;

protected:
	HANDLE m_sharedMemoryHandle = NULL;
	char* m_sharedMemoryView = nullptr;
	size_t m_sharedMemorySize = 0;
};