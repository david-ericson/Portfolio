#ifndef LOGGER
#define LOGGER

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "ExportHeader.h"

using std::vector;
using std::string;

enum Severity { Info, Warning, Error, Severe };

#define LOG( severity, message) Logger::Log( severity, message, __FILE__, __LINE__ )
#define END_LOG Logger::shutDown();

#pragma warning ( disable : 4100)

class Logger
{
public:
#if LOG_ON
	ENGINE_SHARED Logger(void);
	ENGINE_SHARED ~Logger(void);
	ENGINE_SHARED static void StringReplace(string& str, const string& from, const string& to);
	ENGINE_SHARED static string Sanitize(string str);
	ENGINE_SHARED static void Log( Severity severity, const char* message, const char * logFile, int logLine);
	ENGINE_SHARED static void shutDown();
	ENGINE_SHARED static string severityType(int severity);
#else
	Logger(void){}
	~Logger(void){}
	static void StringReplace(string& str, const string& from, const string& to){}
	static string Sanitize(string str){}
	static void Log( Severity severity, const char* message, const char * logFile, int logLine){}
	static void shutDown();
#endif

private:
#if LOG_ON
	ENGINE_SHARED static vector <string> logList;
	ENGINE_SHARED static vector <Severity> severityList;
	ENGINE_SHARED static void WriteFile();
#endif
};

#pragma warning ( default : 4100)

#endif