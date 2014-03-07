#ifndef EVENTCOINDISAPPEARED_H
#define EVENTCOINDISAPPEARED_H

#include "BaseEvent.h"
#include "GameObject.h"

class EventCoinDisappeared :public BaseEvent
{
public:
	EventCoinDisappeared(Common::GameObject* p_pCoin) {m_pCoin = p_pCoin; m_EventType = Event_CoinDisappeared;}
	~EventCoinDisappeared(void);

	Common::GameObject* GetCoin(){return m_pCoin;}

private:
	Common::GameObject* m_pCoin;
};

#endif