#include <WindowsSharedMemory/SharedMemoryToolbox.h>
#include <WindowsSharedMemory/ConfigToolbox.h>
#include <WindowsSharedMemory/FileIOHandler.h>
#include <WindowsSharedMemory/SharedMemoryIOHandler.h>
#include <WindowsSharedMemory/Logger.h>
#include <utility>
#include <memory>

enum class IOHandlerType
{
    FileHandler = 0,
    SharedMemoryHandler
};

using BasicIOHandlerPtr = std::unique_ptr<BasicIOHandler>;
using Handler = std::pair<BasicIOHandlerPtr, IOHandlerType>; //Rename

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        //Add help

        return -1;
    }

    //Change code-style

    const std::string READER_RESOURCE_NAME = std::string(argv[2]);
    const std::string WRITTER_RESOURCE_NAME = std::string(argv[4]);

    //Add argv[] correct input

    const IOHandlerType READER_RESOURCE_TYPE = IOHandlerType((static_cast<int>(argv[1][0]) - 48));
    const IOHandlerType WRITTER_RESOURCE_TYPE = IOHandlerType((static_cast<int>(argv[3][0]) - 48));

    Handler reader = Handler(nullptr, READER_RESOURCE_TYPE);
    Handler writter = Handler(nullptr, WRITTER_RESOURCE_TYPE);

    auto HandlerAssigner = [](Handler& handler, const std::string& resourcePath) -> void {
        switch (handler.second)
        {
        case IOHandlerType::FileHandler:
            handler.first = BasicIOHandlerPtr(new FileIOHandler(resourcePath));
            break;
        case IOHandlerType::SharedMemoryHandler:
            handler.first = BasicIOHandlerPtr(new SharedMemoryIOHandler(resourcePath));
            break;
        default:
            std::cout << "Unknown resource type were passed." << std::endl;
            break;
        };
    };

    HandlerAssigner(reader, READER_RESOURCE_NAME);
    HandlerAssigner(writter, WRITTER_RESOURCE_NAME);

    Logger logger(true);

    std::string fileData;
    fileData.resize(256);

    if (reader.first->Read(&fileData[0], fileData.size()) == true)
    {
        logger.AddLog("[Resource data]: " + fileData);

        if (writter.first->Write(fileData.c_str(), fileData.length()) == true)
        {
            logger.AddLog("Data successfully written to " + WRITTER_RESOURCE_NAME);
        }
    }

    system("pause");

    return 0;
}