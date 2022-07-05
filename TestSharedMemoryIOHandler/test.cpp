#include "pch.h"

#include <WindowsSharedMemory/SharedMemoryIOHandler.h>

const std::string messageToWrite = "TESTING_STRING";
const char* fakeMessageToWrite = nullptr;
const std::string emptyMessageToWrite = "";

const std::string globalValidName = "Global\\MFMO";
const std::string globalInvalidName[2] = { "Global\\\\MFMO",  "Global\\MF\\MO" };

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
	SharedMemoryIOHandler* testIO = new SharedMemoryIOHandler(globalValidName);

	EXPECT_TRUE(testIO->Write(messageToWrite.c_str()));

	delete testIO;
}

TEST(SharedMemoryIOHandlerTestCase, WriteNegativeTest)
{
	SharedMemoryIOHandler* testIO = new SharedMemoryIOHandler(globalValidName);

	EXPECT_TRUE(testIO->Write(fakeMessageToWrite));

	delete testIO;
}

TEST(SharedMemoryIOHandlerTestCase, ReadPositiveTest)
{
	SharedMemoryIOHandler* testIO = new SharedMemoryIOHandler(globalValidName);

	EXPECT_TRUE(testIO->Write(messageToWrite.c_str()));

	std::string buffer;

	EXPECT_TRUE(testIO->Read(buffer));
	EXPECT_EQ(messageToWrite, buffer);

	delete testIO;
}

TEST(SharedMemoryIOHandlerTestCase, ReadNegativeTest)
{
	SharedMemoryIOHandler* testIO = new SharedMemoryIOHandler(globalValidName);

	std::string buffer;

	EXPECT_TRUE(testIO->Read(buffer));
	EXPECT_EQ(emptyMessageToWrite, buffer);

	delete testIO;
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}