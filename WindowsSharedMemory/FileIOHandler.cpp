#include "FileIOHandler.h"

FileIOHandler::FileIOHandler(const std::string& resourcePath):
	BasicIOHandler(resourcePath), m_fileStream(resourcePath, std::ios::in | std::ios::out)
{
	
}

FileIOHandler::~FileIOHandler()
{
	m_fileStream.close();
}

bool FileIOHandler::Read(char* buffer, size_t charToRead)
{
	bool isSuccess = m_fileStream.is_open();

	if (isSuccess == true)
	{
		std::string file;
		std::string tmp_line;

		while (std::getline(m_fileStream, tmp_line))
		{
			file += tmp_line + "\n";
		}
		file.pop_back();

		charToRead = (charToRead > file.length()) ? file.length() : charToRead;
		memcpy_s(buffer, charToRead, file.c_str(), file.length());
	}

	return isSuccess;
}

bool FileIOHandler::Write(const char* data, size_t dataSize)
{
	bool isSuccess = m_fileStream.is_open();

	if (isSuccess == true)
	{
		if (data != nullptr)
		{
			for (int char_index = 0; char_index < dataSize; char_index++)
			{
				m_fileStream << static_cast<char>(data[char_index]);
			}
		}
	}

	return isSuccess;
}

void FileIOHandler::ResetPosition()
{
	m_fileStream.clear();
	m_fileStream.seekg(0, std::ios::beg);
}


