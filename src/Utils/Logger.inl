#include "Utils/Logger.h"

//#include <iostream>
#include <ctime>
namespace Utils
{
	
template<typename... Args>
void Logger::Write(unsigned int lvl, const char* fmt, Args... args)
{
	if (lvl >= m_logLevel)
	{
		std::lock_guard<std::mutex> lock(m_writeMutex);
		m_logStream << GetLineHeader();
		switch (lvl)
		{
		case LVL_INFO:
			m_logStream << "<INFO> :";
			break;
		case LVL_DEBUG:
			m_logStream << "<DEBUG> :";
			break;
		}

		WriteImpl(fmt, args...);

	}
}

template<typename T, typename... TArgs>
void Logger::WriteImpl(const char* fmt, T p1, TArgs... p2)
{
	for (; *fmt != '\0'; fmt++)
	{
		if (*fmt == '%')
		{
			m_logStream << p1;
			WriteImpl(fmt + 1, p2...); // recursive
			return;
		}
		m_logStream << *fmt;
	}
}


}