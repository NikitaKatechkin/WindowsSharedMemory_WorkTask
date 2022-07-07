#include "pch.h"

#include <WindowsSharedMemory/FileIOHandler.h>
#include <memory>

const std::string globalValidName = "cfg.txt";

const size_t MESSAGE_SIZE = 256;

std::string messageToWrite = "TESTING_STRING";
const char* fakeMessageToWrite = nullptr;

TEST(FileIOHandlerTestCase, CreationTest)
{
	FileIOHandler testIO(globalValidName);
}

TEST(FileIOHandlerTestCase, WritePosititveTest)
{
	FileIOHandler testIO(globalValidName);

	EXPECT_TRUE(testIO.Write(messageToWrite.c_str(), messageToWrite.length()));
}

TEST(FileIOHandlerTestCase, WriteNegativeTest)
{
	FileIOHandler testIO(globalValidName);

	EXPECT_TRUE(testIO.Write(fakeMessageToWrite, 0));
}

TEST(FileIOHandlerTestCase, ReadPosititveTest)
{
	FileIOHandler testIO(globalValidName);

	messageToWrite.resize(MESSAGE_SIZE);
	EXPECT_TRUE(testIO.Write(messageToWrite.c_str(), messageToWrite.length()));

	testIO.ResetPosition();

	std::string buffer;
	buffer.resize(MESSAGE_SIZE);

	EXPECT_TRUE(testIO.Read(&buffer[0], buffer.size()));
	EXPECT_EQ(messageToWrite, buffer);
}

TEST(FileIOHandlerTestCase, ReadNegativeTest)
{
	const std::string locaValidName = "cfg.cfg";
	FileIOHandler testIO(locaValidName);

	std::string buffer;
	buffer.resize(MESSAGE_SIZE);

	EXPECT_FALSE(testIO.Read(&buffer[0], buffer.size()));
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}