#ifndef EVENTCOINSPAWNED_H
#define EVENTCOINSPAWNED_H

#include "BaseEvent.h"
#include "GameObject.h"

class EventCoinSpawned : public BaseEvent
{
public:
	EventCoinSpawned(Common::GameObject* p_pCoin) {m_pCoin = p_pCoin; m_EventType = Event_CoinSpawned;}
	~EventCoinSpawned(void);

	Common::GameObject* GetCoin(){return m_pCoin;}
private:
	Common::GameObject *m_pCoin;
};

#endif
