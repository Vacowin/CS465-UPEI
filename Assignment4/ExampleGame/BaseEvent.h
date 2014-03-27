
#ifndef BASEEVENT_H
#define BASEEVENT_H

enum EventType
{
	Event_CoinSpawned,
	Event_CoinDisappeared,
	Event_ObjectCollision,
	Event_CharacterCollision,
	Event_CoinCollected
};

class BaseEvent
{
public:
	virtual EventType GetEventType(){return m_EventType;}

protected:
	EventType m_EventType;
};



#endif