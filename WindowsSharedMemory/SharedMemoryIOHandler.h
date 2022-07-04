#pragma once

#include <windows.h>
#include <codecvt>
#include <locale>
#include "BasicIOHandler.h"

class SharedMemoryIOHandler final : public BasicIOHandler
{
public:
	SharedMemoryIOHandler(const std::string& resourcePath);
	~SharedMemoryIOHandler();

	bool Read(std::string& buffer) override;
	bool Write(const char* data) override;

protected:
	HANDLE m_sharedMemoryHandle = NULL;

protected:
	bool Open();
	void Close();
};