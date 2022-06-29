#include <windows.h>
#include <iostream>
#include <fstream>
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
	const std::string writter_cfg_path = "../WindowsSharedMemoryWritter/cfg.txt";
	const std::string reader_cfg_path = "../WindowsSharedMemoryReader/cfg.txt";

	if (ReadConfig(writter_cfg_path) == ReadConfig(reader_cfg_path))
	{
		std::cout << "Success." << std::endl;

	}
	else
	{
		std::cout << "Fail." << std::endl;
	}

	return 0;
}