#ifndef EVENTCOINCOLLECTED_H
#define EVENTCOINCOLLECTED_H

#include "BaseEvent.h"
#include "GameObject.h"

class EventCoinCollected : public BaseEvent
{
public:
	EventCoinCollected(Common::GameObject* p_pChar, Common::GameObject* p_pCoin)
	{m_pCharacter = p_pChar;m_pCoin = p_pCoin; m_EventType = Event_CoinCollected;};
	~EventCoinCollected(void);

	Common::GameObject* GetCharacter(){return m_pCharacter;}
	Common::GameObject* GetCoin(){return m_pCoin;}
private:
	Common::GameObject *m_pCharacter;
	Common::GameObject *m_pCoin;
};


#endif