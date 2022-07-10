#include "pch.h"

#include <WindowsSharedMemory/SharedMemoryIOHandler.h>

const size_t MESSAGE_SIZE = 256;

std::string messageToWrite = "TESTING_STRING";
const char* fakeMessageToWrite = nullptr;
std::string emptyMessageToWrite = "";

const std::string globalValidName = "Global\\MFMO";
const std::string globalInvalidName[2] = { "Global\\\\MFMO",  "Global\\MF\\MO" };

using converter = std::wstring_convert<std::codecvt_utf8<wchar_t>>;

TEST(SharedMemoryIOHandlerTestCase, CreationPositiveTest)
{
	SharedMemoryIOHandler* testIO = new SharedMemoryIOHandler(globalValidName);
	delete testIO;

	testIO = new SharedMemoryIOHandler("Local\\MLFMO");
	delete testIO;

	testIO = new SharedMemoryIOHandler("MPFMO");
	delete testIO;

	testIO = new SharedMemoryIOHandler("cfg.txt");
	delete testIO;
}

TEST(SharedMemoryIOHandlerTestCase, CreationNegativeTest)
{
	EXPECT_ANY_THROW(SharedMemoryIOHandler(globalInvalidName[0].c_str()));
	EXPECT_ANY_THROW(SharedMemoryIOHandler(globalInvalidName[1].c_str()));
}

TEST(SharedMemoryIOHandlerTestCase, WritePositiveTest)
{
	SharedMemoryIOHandler testIO(globalValidName);

	messageToWrite.resize(MESSAGE_SIZE);
	EXPECT_TRUE(testIO.Write(messageToWrite.c_str(), messageToWrite.length()));

	auto sharedMemoryReadHandle = CreateFileMapping(INVALID_HANDLE_VALUE,
													nullptr,
													PAGE_READWRITE,
													0,
													static_cast<DWORD>(MESSAGE_SIZE),
													converter().from_bytes(globalValidName).c_str());

	EXPECT_FALSE(sharedMemoryReadHandle == NULL);

	auto sharedMemoryReadView = static_cast<char*>(MapViewOfFile(sharedMemoryReadHandle,
																 FILE_MAP_ALL_ACCESS,
																 0,
																 0,
																 MESSAGE_SIZE));

	EXPECT_FALSE(sharedMemoryReadView == nullptr);
	EXPECT_EQ(memcmp(sharedMemoryReadView, messageToWrite.c_str(), MESSAGE_SIZE), 0);

	CloseHandle(sharedMemoryReadHandle);
}

TEST(SharedMemoryIOHandlerTestCase, WriteNegativeTest)
{
	SharedMemoryIOHandler testIO(globalValidName);

	EXPECT_FALSE(testIO.Write(fakeMessageToWrite, 0));
}

TEST(SharedMemoryIOHandlerTestCase, ReadPositiveTest)
{
	SharedMemoryIOHandler testIO(globalValidName);

	messageToWrite.resize(MESSAGE_SIZE);
	EXPECT_TRUE(testIO.Write(messageToWrite.c_str(), messageToWrite.length()));

	std::string buffer;
	buffer.resize(MESSAGE_SIZE);

	EXPECT_TRUE(testIO.Read(&buffer[0], buffer.size()));
	EXPECT_EQ(messageToWrite, buffer);
}

TEST(SharedMemoryIOHandlerTestCase, ReadNegativeTest)
{
	SharedMemoryIOHandler testIO(globalValidName);
	emptyMessageToWrite.resize(MESSAGE_SIZE);

	std::string buffer;
	buffer.resize(MESSAGE_SIZE);

	EXPECT_TRUE(testIO.Read(&buffer[0], buffer.size()));

	EXPECT_EQ(emptyMessageToWrite, buffer);

	EXPECT_FALSE(testIO.Read(nullptr, buffer.size()));
	EXPECT_FALSE(testIO.Read(&buffer[0], 0));
	EXPECT_FALSE(testIO.Read(nullptr, 0));

}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}