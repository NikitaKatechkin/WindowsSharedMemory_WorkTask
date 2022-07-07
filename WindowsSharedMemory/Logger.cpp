#include "Logger.h"

Logger::Logger(const bool isMuted, const std::string& logFilePath):
	m_logFilePath(logFilePath), m_isMuted(isMuted)
{
}

Logger::~Logger()
{
	std::ofstream logFile(m_logFilePath);

	if (logFile.is_open() == true)
	{
		logFile << m_logHostory;
	}

	logFile.close();
}

void Logger::ChangeDisplayMode(const bool isMuted)
{
	m_isMuted = isMuted;
}

void Logger::AddLog(std::string log)
{
	if (m_isMuted == false)
	{
		std::cout << log << std::endl;
	}

	m_logHostory += (log + "\n");
}
