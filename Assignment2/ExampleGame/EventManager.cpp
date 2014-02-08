#include "EventManager.h"
#include <algorithm>

EventManager* EventManager::s_pEventManagerInstance = NULL;


EventManager::EventManager()
{
	EventList m_lEventList = EventList();
	ListenerMap m_mListenerMap = ListenerMap();
}

void EventManager::CreateInstance(){
	assert(s_pEventManagerInstance == NULL);
	s_pEventManagerInstance = new EventManager();
}

void EventManager::DestroyInstance()
{
	assert(s_pEventManagerInstance != NULL);
	delete s_pEventManagerInstance;
	s_pEventManagerInstance = NULL;
}

EventManager* EventManager::Instance()
{
	assert(s_pEventManagerInstance);
	return s_pEventManagerInstance;
}

void EventManager::QueueEvent(BaseEvent* p_pBaseEvent)
{
	ListenerMap::iterator it = m_mListenerMap.find(p_pBaseEvent->GetEventType());
	if (it!= m_mListenerMap.end())
	{
		m_lEventList.push_back(p_pBaseEvent);
	}
}

void EventManager::TriggerEvent(BaseEvent* p_pBaseEvent)
{
	ListenerMap::iterator it = m_mListenerMap.find(p_pBaseEvent->GetEventType());
	if (it!=m_mListenerMap.end())
	{
		ListenerList &listenerList = it->second;
		for (int i=0;i<listenerList.size();i++)
		{
			EventListener eventDelegate = listenerList.at(i);
			eventDelegate(p_pBaseEvent);
		}
	}
}

void EventManager::AddListener(EventType p_EventType, EventListener p_EvenListener)
{
	ListenerMap::iterator it = m_mListenerMap.find(p_EventType);
	if (it!=m_mListenerMap.end())
	{
		ListenerList &listenerList = it->second;
		listenerList.push_back(p_EvenListener);
	}
	else
	{
		ListenerList listenerList = ListenerList();
		listenerList.push_back(p_EvenListener);
		m_mListenerMap.insert(std::make_pair<EventType, ListenerList>(p_EventType, listenerList));
	}

}

void EventManager::RemoveListerner(EventType p_EventType, EventListener p_EvenListener)
{
	/*ListenerMap::iterator it = m_mListenerMap.find(p_EventType);
	if (it!=m_mListenerMap.end())
	{
		ListenerList listenerList = it->second;
		for (int i=0;i<listenerList.size();i++)
		{
			EventListener eventDelegate = listenerList.at(i);
			if (eventDelegate == p_EvenListener)
		}
	}*/
}

void EventManager::Update(float p_fDelta)
{
	while (!m_lEventList.empty())
	{
		BaseEvent *pBaseEvent = m_lEventList.back();
		m_lEventList.pop_back();

		TriggerEvent(pBaseEvent);
	}
}