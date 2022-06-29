#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <string>

std::string ReadConfig(std::string configFile)
{
	std::string result;
	std::string line;

	std::ifstream myfile("cfg.txt");
	if (myfile.is_open())
	{
		while (std::getline(myfile, line))
		{
			std::cout << line << std::endl;
			result += (line + "\n");
		}
	}
	myfile.close();

	return result;
}

int main()
{
	const unsigned int BUF_SIZE = 256;
	const std::wstring SHARED_MEMORY_NAME = L"Global\\MyFileMappingObject";

	HANDLE mapFile = CreateFileMapping(INVALID_HANDLE_VALUE, 
									   nullptr, 
									   PAGE_READWRITE, 
									   0, 
									   BUF_SIZE, 
									   SHARED_MEMORY_NAME.c_str());

	if (mapFile != NULL)
	{
		std::wcout << L"Successfully create file mapping object." << std::endl;

		const char* viewBuffer = static_cast<const char*>(MapViewOfFile(mapFile, 
																FILE_MAP_ALL_ACCESS, 
																0, 
																0, 
																BUF_SIZE));

		if (viewBuffer != NULL)
		{
			std::wcout << L"Successfully map view of file." << std::endl;
			
			std::string messageToWrite = ReadConfig("cfg.txt");

			CopyMemory(static_cast<PVOID>(const_cast<LPSTR>(viewBuffer)),
					   messageToWrite.c_str(),
					   (messageToWrite.length() * sizeof(char)));
			
			//std::this_thread::sleep_for(std::chrono::seconds(5));
			system("pause");
			
			UnmapViewOfFile(viewBuffer);
			CloseHandle(mapFile);
		}
		else
		{
			std::wcout << L"Failed to map view of file." << std::endl;
			std::wcout << L"GLE = " << GetLastError() << "." << std::endl;

			CloseHandle(mapFile);
		}
	}
	else
	{
		std::wcout << L"Failed to create file mapping object." << std::endl;
		std::wcout << L"GLE = " << GetLastError() << "." << std::endl;
	}

	return 0;
}