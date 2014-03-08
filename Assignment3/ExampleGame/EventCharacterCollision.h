#ifndef EVENTCHARACTERCOLLISION_H
#define EVENTCHARACTERCOLLISION_H

#include "Assignment3\ExampleGame\BaseEvent.h"
#include "GameObject.h"

class EventCharacterCollision : public BaseEvent
{
public:
	EventCharacterCollision(Common::GameObject* p_pCharacter, Common::GameObject* p_pObject)
	{m_pCharacter = p_pCharacter;m_pGameObject = p_pObject; m_EventType = Event_ObjectCollision;};
	~EventCharacterCollision(void);
	
	Common::GameObject* GetCharacter(){return m_pCharacter;}
	Common::GameObject* GetGameObject(){return m_pGameObject;}

private:
	Common::GameObject *m_pCharacter;
	Common::GameObject *m_pGameObject;
};

#endif