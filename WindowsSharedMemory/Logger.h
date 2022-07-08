#pragma once

#include <iostream>
#include <fstream>

class Logger final
{
public:
	Logger(const bool isMuted = false, const std::string& logFilePath = "./log.txt");
	~Logger();

	void ChangeDisplayMode(const bool isMuted);
	void AddLog(std::string log);

private:
	std::string m_logFilePath;
	std::string m_logHistory;
	bool m_isMuted = false;
};