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

	messageToWrite.resize(MESSAGE_SIZE);
	EXPECT_TRUE(testIO.Write(messageToWrite.c_str(), messageToWrite.length()));

	std::ifstream dataChecker(globalValidName);

	EXPECT_TRUE(dataChecker.is_open());

	std::string tmp_line, file;
	while (std::getline(dataChecker, tmp_line))
	{
		file += tmp_line + "\n";
	}
	file.pop_back();

	EXPECT_EQ(file, messageToWrite);
}

TEST(FileIOHandlerTestCase, WriteNegativeTest)
{
	FileIOHandler testIO(globalValidName);

	EXPECT_FALSE(testIO.Write(fakeMessageToWrite, 256));
	EXPECT_FALSE(testIO.Write(messageToWrite.c_str(), 0));
	EXPECT_FALSE(testIO.Write(fakeMessageToWrite, 0));
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

	FileIOHandler correctTestIO(globalValidName);

	EXPECT_FALSE(testIO.Read(&buffer[0], 0));
	EXPECT_FALSE(testIO.Read(const_cast<char*>(fakeMessageToWrite), 256));
	EXPECT_FALSE(testIO.Read(const_cast<char*>(fakeMessageToWrite), 0));
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}