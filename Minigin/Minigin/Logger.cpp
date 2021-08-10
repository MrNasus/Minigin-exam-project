#include "MiniginPCH.h"
#include "Logger.h"
#include <iostream>

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Activate()
{
	std::cout << "LOGGER ACTIVATE\n";
}
