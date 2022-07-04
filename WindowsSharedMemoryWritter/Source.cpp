#include <WindowsSharedMemory/SharedMemoryToolbox.h>
#include <WindowsSharedMemory/ConfigToolbox.h>
#include <WindowsSharedMemory/FileIOHandler.h>
#include <WindowsSharedMemory/SharedMemoryIOHandler.h>
#include <utility>

enum class IOHandlerType
{
    FileHandler = 0,
    SharedMemoryHandler
};

using Handler = std::pair<BasicIOHandler*, IOHandlerType>;

int main(int argc, char* argv[])
{
    for (size_t index = 0; index < argc; index++)
    {
        std::cout << "Index[" << index << "]: " << std::string(argv[index]) << std::endl;
    }

    std::string READER_RESOURCE_NAME = std::string(argv[2]);
    std::string WRITTER_RESOURCE_NAME = std::string(argv[4]).c_str();

    Handler reader = Handler(nullptr, IOHandlerType((static_cast<int>(argv[1][0]) - 48)));
    Handler writter = Handler(nullptr, IOHandlerType((static_cast<int>(argv[3][0]) - 48)));

    switch (reader.second)
    {
    case IOHandlerType::FileHandler:
        reader.first = new FileIOHandler(READER_RESOURCE_NAME);
        break;
    case IOHandlerType::SharedMemoryHandler:
        reader.first = new SharedMemoryIOHandler(READER_RESOURCE_NAME);
        break;
    default:
        break;
    }

    switch (writter.second)
    {
    case IOHandlerType::FileHandler:
        writter.first = new FileIOHandler(WRITTER_RESOURCE_NAME);
        break;
    case IOHandlerType::SharedMemoryHandler:
        writter.first = new SharedMemoryIOHandler(WRITTER_RESOURCE_NAME);
        break;
    default:
        break;
    }

    std::string fileData;
    if (reader.first->Read(fileData) == true)
    {
        if (writter.first->Write(fileData.c_str()) == true)
        {
            std::cout << "Nice!!!" << std::endl;
        }
    }

    system("pause");

    delete reader.first;
    delete writter.first;

    return 0;
}