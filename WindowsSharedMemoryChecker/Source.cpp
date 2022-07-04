#include <WindowsSharedMemory/ConfigToolbox.h>

int main()
{
	const std::string writter_cfg_path = "../WindowsSharedMemoryWritter/cfg.txt";
	const std::string reader_cfg_path = "../WindowsSharedMemoryReader/cfg.txt";

	if (ConfigToolbox::ReadConfig(writter_cfg_path) == ConfigToolbox::ReadConfig(reader_cfg_path))
	{
		std::cout << "Success." << std::endl;
	}
	else
	{
		std::cout << "Fail." << std::endl;
	}

	return 0;
}