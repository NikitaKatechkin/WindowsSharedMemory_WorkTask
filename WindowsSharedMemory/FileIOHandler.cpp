#include "FileIOHandler.h"

FileIOHandler::FileIOHandler(const std::string& resourcePath):
	BasicIOHandler(resourcePath), m_fileStream(resourcePath, std::ios::in | std::ios::out)
{
	
}

FileIOHandler::~FileIOHandler()
{
	m_fileStream.close();
}

bool FileIOHandler::Read(char* buffer, size_t charToRead) //const param
{
	if (m_fileStream.is_open() == false || buffer == nullptr || charToRead <= 0)
	{
		return false;
	}

	std::string file;
	std::string tmp_line;

	while (std::getline(m_fileStream, tmp_line))
	{
		file += tmp_line + "\n";
	}
	file.pop_back();

	memcpy_s(buffer, (charToRead > file.length()) ? file.length() : charToRead, 
				file.c_str(), file.length());
	

	return true;
}

bool FileIOHandler::Write(const char* data, size_t dataSize) //const param
{
	if (m_fileStream.is_open() == false || data == nullptr || dataSize <= 0)
	{
		return false;
	}

	for (int i = 0; i < dataSize; i++)
	{
		m_fileStream << static_cast<char>(data[i]);
	}
	
	return true;
}

void FileIOHandler::ResetPosition()
{
	m_fileStream.clear();
	m_fileStream.seekg(0, std::ios::beg);
}


