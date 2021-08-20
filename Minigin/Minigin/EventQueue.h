#pragma once
#include "Event.h"
#include <vector>

namespace minigin
{
	class EventQueue
	{
	public:
		EventQueue(size_t queueSize);
		~EventQueue() = default;

		EventQueue(const EventQueue& other) = delete;
		EventQueue(EventQueue&& other) = delete;
		EventQueue& operator=(const EventQueue& other) = delete;
		EventQueue& operator=(EventQueue&& other) = delete;

		bool PushEvent(const Event& event);
		bool PopEvent(Event& event);
		const std::vector<Event>& GetPendingQueue();
		void ResetQueue();

	private:
		std::vector<Event> m_Queue;
		std::vector<Event> m_PendingQueue;
		bool m_IsPendingQueueUpdated;
		size_t m_Head;
		size_t m_Tail;
		size_t m_QueueSize;
	};
}