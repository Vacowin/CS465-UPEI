#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "BaseEvent.h"
#include <vector>
#include <functional>
#include <map>
#include <assert.h>

typedef std::vector<BaseEvent*> EventList;
typedef std::tr1::function<void (BaseEvent*)> EventListener;
typedef std::vector<EventListener> ListenerList;
typedef std::map<EventType, ListenerList> ListenerMap;

class EventManager
{
public:
	
	static void CreateInstance();
	static void DestroyInstance();
	static EventManager* Instance();

	void QueueEvent(BaseEvent* p_pBaseEvent);
	void TriggerEvent(BaseEvent* p_pBaseEvent);
	void Update(float p_fDelta);
	void AddListener(EventType p_EventType, EventListener p_EvenListener);
	void RemoveListerner(EventType p_EventType, EventListener p_EvenListener);


private:
	EventManager();
	virtual ~EventManager(){};
	static EventManager* s_pEventManagerInstance;

	EventList m_lEventList;
	ListenerMap m_mListenerMap;
};

#endif