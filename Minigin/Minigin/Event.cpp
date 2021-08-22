#include "MiniginPCH.h"
#include "Event.h"

using namespace minigin;

Event::Event(const std::string& name)
	:m_Name{name}
{
}

Event::Event(const Event& other)
	: m_Name{ other.m_Name }
{
}

Event::Event(Event&& other)
	: m_Name{ other.m_Name }
{
}

Event& Event::operator=(const Event& other)
{
	m_Name = other.m_Name;
	return *this;
}

Event& Event::operator=(Event&& other)
{
	m_Name = other.m_Name;
	return *this;
}
