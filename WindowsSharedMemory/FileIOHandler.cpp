#include "FileIOHandler.h"

FileIOHandler::FileIOHandler(const std::string& resourcePath):
	BasicIOHandler(resourcePath)
{
}

bool FileIOHandler::Read(std::string& buffer)
{
	std::ifstream readFile(m_resourcePath);

	bool isSuccess = readFile.is_open();
	std::string tmp_line;
	
	if (isSuccess == true)
	{
		while (std::getline(readFile, tmp_line))
		{
			buffer += (tmp_line + "\n");
		}
	}

	readFile.close();

	return isSuccess;
}

bool FileIOHandler::Write(const char* data)
{
	std::ofstream writeFile(m_resourcePath);

	bool isSuccess = writeFile.is_open();

	if (isSuccess == true)
	{
		for (int char_index = 0; char_index < strlen(data); char_index++)
		{
			writeFile << static_cast<char>(data[char_index]);
		}
	}

	writeFile.close();

	return isSuccess;
}
