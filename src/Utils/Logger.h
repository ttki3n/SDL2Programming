#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <mutex>
#include <memory>

#define LOG_LOG(lvl, fmt, ...) \
	Utils::SimpleLogger::_log.Write(lvl, fmt, ##__VA_ARGS__)

#define LOG_INFO(fmt, ...) \
	LOG_LOG(Utils::Logger::LVL_INFO, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) \
	LOG_LOG(Utils::Logger::LVL_ERROR, fmt, ##__VA_ARGS__)

namespace Utils
{

// default instance of logger
// forward declaration
class Logger;

class SimpleLogger
{
public:
	static Logger _log;			

};

//class SimpleLogger: public Logger
//{
//public:
//	static SimpleLogger& GetInstance()
//	{
//		static SimpleLogger ins(Logger::LVL_INFO, Logger::LOGTO_CONSOLE_AND_FILE, "log.txt");			
//		return ins;
//	}
//	SimpleLogger(SimpleLogger const&) = delete;
//	void operator=(SimpleLogger const&) = delete;
//	
//
//private:
//	SimpleLogger() {}
//	SimpleLogger(Logger::LOG_LEVEL lvl, Logger::LOG_POLICY p, const std::string& filename)
//		:Logger(lvl, p, filename)
//	{}
//
//
//
//};

	
	
	
class Logger
{
public:

	enum LOG_LEVEL
	{
		LVL_INFO = 0,
		LVL_DEBUG,
		LVL_WARNING,
		LVL_ERROR
	};

	enum LOG_POLICY
	{
		LOGTO_CONSOLE = 0,
		LOGTO_FILE ,
		LOGTO_CONSOLE_AND_FILE
	};
	Logger();
	Logger(unsigned int lvl, unsigned int policy, const std::string& filename);
	~Logger();

	void OpenFile(const std::string& filename);
	void CloseFile();
	
	void SetLogLevel(unsigned int lvl);
	void SetLogPolicy(unsigned int policy);	
	
	template<typename... Args>
	void Write(unsigned int lvl, const char* fmt, Args... args);

	void WriteImpl(const char* fmt);
	template<typename T, typename... TArgs>
	void WriteImpl(const char* fmt, T p1, TArgs... p2); // recursive variadic function
	std::string GetTime();
	std::string GetLineHeader();
protected:
	unsigned int m_logLevel;
	unsigned int m_logPolicy;
	std::stringstream m_logStream;
	std::unique_ptr<std::ofstream> m_ofStreamPtr;
	std::mutex m_writeMutex;

};


}

#include "Logger.inl"