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

BasicIOHandler* HandlerAssigner(const IOHandlerType& handlerType, const std::string& resourcePath)
{
    BasicIOHandler* result = nullptr;

    switch (handlerType)
    {
    case IOHandlerType::FileHandler:
        result = new FileIOHandler(resourcePath);
        break;
    case IOHandlerType::SharedMemoryHandler:
        result = new SharedMemoryIOHandler(resourcePath);
        break;
    default:
        std::cout << "Unknown resource type were passed." << std::endl;
        break;
    };

    return result;
}

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        std::cout << "Wrong amount of arguments were passed to programm." << std::endl;
        std::cout << "programm [type FROM resource] [path to FROM resource] ";
        std::cout << "[type TO resource] [path to TO resource]";
        std::cout << std::endl;

        return -1;
    }

    const std::string READER_RESOURCE_NAME = std::string(argv[2]);
    const std::string WRITTER_RESOURCE_NAME = std::string(argv[4]);

    auto typeValidator = [](int argType) -> bool { return (argType == 0 || argType == 1); };

    if ((typeValidator(static_cast<int>(argv[1][0]) - 48) == false) ||
        (typeValidator(static_cast<int>(argv[3][0]) - 48) == false))
    {
        std::cout << "Non valid resource types were provided." << std::endl;

        return -1;
    }

    const IOHandlerType READER_RESOURCE_TYPE = IOHandlerType((static_cast<int>(argv[1][0]) - 48));
    const IOHandlerType WRITTER_RESOURCE_TYPE = IOHandlerType((static_cast<int>(argv[3][0]) - 48));

    BasicIOHandler* reader = HandlerAssigner(READER_RESOURCE_TYPE, READER_RESOURCE_NAME);;
    BasicIOHandler* writter = HandlerAssigner(WRITTER_RESOURCE_TYPE, WRITTER_RESOURCE_NAME);;

    Logger consoleLogger;
    Logger fileLogger("./log.txt");

    const size_t BUFFER_SIZE = 256;

    std::string fileData;
    fileData.resize(BUFFER_SIZE);

    if (reader->Read(&fileData[0], fileData.size()) == true)
    {
        consoleLogger.AddLog("[Resource data]: " + fileData);
        fileLogger.AddLog("[Resource data]: " + fileData);

        if (writter->Write(fileData.c_str(), fileData.length()) == true)
        {
            consoleLogger.AddLog("Data successfully written to " + WRITTER_RESOURCE_NAME);
            fileLogger.AddLog("Data successfully written to " + WRITTER_RESOURCE_NAME);
        }
    }

    system("pause");

    delete reader;
    delete writter;

    return 0;
}