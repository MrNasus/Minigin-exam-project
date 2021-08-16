#include "MiniginPCH.h"
#include "Logger.h"
#include <iostream>

using namespace minigin;

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
