#pragma once
#include <string>

class BasicIOHandler
{
public:
	BasicIOHandler(const std::string& resourcePath);
	virtual ~BasicIOHandler() = default;

	virtual bool Read(char* buffer, size_t charToRead) = 0;
	virtual bool Write(const char* data, size_t dataSize) = 0;
protected:
	std::string m_resourcePath;
};