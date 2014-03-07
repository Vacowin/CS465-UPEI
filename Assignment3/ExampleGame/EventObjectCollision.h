#ifndef EVENTOBJECTCOLLISION_H
#define EVENTOBJECTCOLLISION_H

#include "BaseEvent.h"
#include "GameObject.h"

class EventObjectCollision : public BaseEvent
{
public:
	EventObjectCollision(Common::GameObject* p_pObject1, Common::GameObject* p_pObject2)
	{m_pGameObject1 = p_pObject1;m_pGameObject2 = p_pObject2; m_EventType = Event_ObjectCollision;};
	~EventObjectCollision(void);
	
	Common::GameObject* GetGameObject1(){return m_pGameObject1;}
	Common::GameObject* GetGameObject2(){return m_pGameObject2;}

private:
	Common::GameObject *m_pGameObject1;
	Common::GameObject *m_pGameObject2;
};

#endif