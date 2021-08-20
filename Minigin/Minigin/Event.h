#pragma once
#include <string>

namespace minigin
{

	class Event
	{
	public:
		Event(const std::string& name);
		virtual ~Event() = default;

		Event(const Event& other);
		Event(Event&& other);
		Event& operator=(const Event& other);
		Event& operator=(Event&& other);

	private:
		std::string m_Name;
	};

}