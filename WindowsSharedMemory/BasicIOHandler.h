#pragma once
#include <string>

class BasicIOHandler
{
public:
	BasicIOHandler(const std::string& resourcePath);
	virtual ~BasicIOHandler() = default;

	virtual bool Read(std::string& buffer) = 0;
	virtual bool Write(const char* data) = 0;
protected:
	std::string m_resourcePath;
};