#pragma once

#include <fstream>
#include <iostream>
#include "BasicIOHandler.h"

class FileIOHandler final : public BasicIOHandler
{
public:
	FileIOHandler(const std::string& resourcePath);
	~FileIOHandler() = default;

	bool Read(std::string& buffer) override;
	bool Write(const char* data) override;
protected:
};