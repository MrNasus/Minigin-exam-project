#include "MiniginPCH.h"
#include "EventQueue.h"

using namespace minigin;

EventQueue::EventQueue(size_t queueSize)
	: m_Queue{}
	,m_QueueSize{queueSize}
	,m_PendingQueue{}
	,m_Head{0}
	,m_Tail{0}
	,m_IsPendingQueueUpdated{true}
{
	if (m_QueueSize < 1)
	{
		m_QueueSize = 1;
	}
	m_Queue.resize(m_QueueSize, Event{ "MT" });
}

bool EventQueue::PushEvent(const Event& event)
{
	if (m_Tail == m_Head)
	{
		std::cout << "queue is full";
		return false;
	}
	m_Queue[m_Tail] = event;
	++m_Tail;
	m_Tail %= m_QueueSize;
	m_IsPendingQueueUpdated = false;
	return true;
}

bool EventQueue::PopEvent(Event& event)
{
	if (m_Head == m_Tail)
	{
		std::cout << "queue is empty";
		return false;
	}
	event = m_Queue[m_Head];
	++m_Head;
	m_Head %= m_QueueSize;
	m_IsPendingQueueUpdated = false;
	return true;
}

const std::vector<Event>& EventQueue::GetPendingQueue()
{
	if (!m_IsPendingQueueUpdated)
	{
		std::vector<Event> sortedQueue{};
		size_t currentQueueSize;
		size_t head{m_Head};
		size_t tail{m_Tail};
		if (head <= tail)
		{
			currentQueueSize = tail - head;
		}
		else
		{
			currentQueueSize = m_QueueSize - head + tail;
		}
		sortedQueue.reserve(currentQueueSize);
		while (head < tail)
		{
			sortedQueue.push_back(m_Queue[head]);
			++head;
		}
		m_PendingQueue = sortedQueue;
		m_IsPendingQueueUpdated = true;
	}
	return m_PendingQueue;
}

void EventQueue::ResetQueue()
{
	Event temp{"t"};
	while (PopEvent(temp))
	{

	}
}
