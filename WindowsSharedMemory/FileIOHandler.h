#pragma once

#include <fstream>
#include <iostream>
#include "BasicIOHandler.h"

class FileIOHandler final : public BasicIOHandler
{
public:
	FileIOHandler(const std::string& resourcePath);
	virtual ~FileIOHandler();

	virtual bool Read(char* buffer, size_t charToRead) override;
	virtual bool Write(const char* data, size_t dataSize) override;

	void ResetPosition();
protected:
	std::fstream m_fileStream;
};