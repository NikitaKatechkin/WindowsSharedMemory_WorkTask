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

    auto typeValidator = [](int argType) -> bool { return (argType == 0 || argType == 1); };

    if ((typeValidator(static_cast<int>(argv[1][0]) - 48) == false) ||
        (typeValidator(static_cast<int>(argv[3][0]) - 48) == false))
    {
        std::cout << "Non valid resource types were provided." << std::endl;

        return -1;
    }

    const std::string readerResourceName = std::string(argv[2]);
    const std::string writterResourceName = std::string(argv[4]);

    const IOHandlerType readerResourceType = IOHandlerType((static_cast<int>(argv[1][0]) - 48));
    const IOHandlerType writterResourceType = IOHandlerType((static_cast<int>(argv[3][0]) - 48));

    BasicIOHandler* reader = HandlerAssigner(readerResourceType, readerResourceName);
    BasicIOHandler* writter = HandlerAssigner(writterResourceType, writterResourceName);

    Logger consoleLogger;
    Logger fileLogger("./log.txt");

    const size_t bufferSize = 256;

    std::string fileData;
    fileData.resize(bufferSize);

    if (reader->Read(&fileData[0], fileData.size()) == true)
    {
        consoleLogger << ("[Resource data]: " + fileData);
        fileLogger << ("[Resource data]: " + fileData);

        if (writter->Write(fileData.c_str(), fileData.length()) == true)
        {
            consoleLogger << ("Data successfully written to " + writterResourceName);
            fileLogger << ("Data successfully written to " + writterResourceName);
        }
    }

    system("pause");

    delete reader;
    delete writter;

    return 0;
}