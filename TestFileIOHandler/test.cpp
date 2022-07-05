#include "pch.h"

#include <WindowsSharedMemory/FileIOHandler.h>

const std::string globalValidName = "cfg.txt";

const std::string messageToWrite = "TESTING_STRING";
const char* fakeMessageToWrite = nullptr;

TEST(FileIOHandlerTestCase, CreationTest)
{
	FileIOHandler* testIO = new FileIOHandler(globalValidName);
	delete testIO;
}

TEST(FileIOHandlerTestCase, WritePosititveTest)
{
	FileIOHandler* testIO = new FileIOHandler(globalValidName);

	EXPECT_TRUE(testIO->Write(messageToWrite.c_str()));

	delete testIO;
}

TEST(FileIOHandlerTestCase, WriteNegativeTest)
{
	FileIOHandler* testIO = new FileIOHandler(globalValidName);

	EXPECT_TRUE(testIO->Write(fakeMessageToWrite));

	delete testIO;
}

TEST(FileIOHandlerTestCase, ReadPosititveTest)
{
	FileIOHandler* testIO = new FileIOHandler(globalValidName);

	EXPECT_TRUE(testIO->Write(messageToWrite.c_str()));

	std::string buffer;

	EXPECT_TRUE(testIO->Read(buffer));
	EXPECT_EQ(messageToWrite, buffer);

	delete testIO;
}

TEST(FileIOHandlerTestCase, ReadNegativeTest)
{
	const std::string locaValidName = "cfg.cfg";
	FileIOHandler* testIO = new FileIOHandler(locaValidName);

	std::string buffer;
	EXPECT_FALSE(testIO->Read(buffer));

	delete testIO;
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}