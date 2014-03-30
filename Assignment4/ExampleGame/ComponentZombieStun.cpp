#include "ComponentZombieStun.h"
#include "EventManager.h"
#include "EventObjectCollision.h"
#include "Assignment4\ExampleGame\src\ComponentAnimController.h"
#include "Assignment4\ExampleGame\ComponentAIController.h"
using namespace week2;

ComponentZombieStun::ComponentZombieStun(float p_fDuration)
{
	m_fDuration = p_fDuration;
	m_bIsStunned = false;
	m_fStunTime = 0;

	EventListener eventListener1 = std::tr1::bind(&ComponentZombieStun::HandleProjectileCollision, this, std::tr1::placeholders::_1);
	EventManager::Instance()->AddListener(Event_ObjectCollision, eventListener1);
}

Common::ComponentBase* ComponentZombieStun::CreateComponent(TiXmlNode* p_pNode)
{
	assert(strcmp(p_pNode->Value(), "GOC_ZombieStun") == 0);
	float fDurarion = 0.0f;

	TiXmlNode* pChildNode = p_pNode->FirstChild("Duration");
	if (pChildNode)
	{
		TiXmlElement* pElement = pChildNode->ToElement();

		pElement->QueryFloatAttribute("value",&fDurarion);
	}
	ComponentZombieStun* pZombieStun = new ComponentZombieStun(fDurarion);

	return pZombieStun;
}

void ComponentZombieStun::Update(float p_fDelta)
{
	if (m_bIsStunned)
	{
		m_fStunTime +=p_fDelta;
		if (m_fStunTime > m_fDuration)
		{
			m_bIsStunned = false;
			m_fStunTime = 0;
			ComponentAnimController *pAni = static_cast<ComponentAnimController*>(this->GetGameObject()->GetComponent("GOC_AnimController"));
			pAni->SetAnim("walk");
			ComponentAIController *pAI = static_cast<ComponentAIController*>(this->GetGameObject()->GetComponent("GOC_AIController"));
			if (pAI->GetCurrentState() == AIState::eAIState_ChasingCoin)
				pAni->SetAnim("run");
		}
	}
}

void ComponentZombieStun::HandleProjectileCollision(BaseEvent *p_Event)
{
	EventObjectCollision *pEventCollision = static_cast<EventObjectCollision*>(p_Event);
	Common::GameObject* pGameObjectA = pEventCollision->GetGameObject1();
	Common::GameObject* pGameObjectB = pEventCollision->GetGameObject2();
	
	Common::GameObject* pProjectTile = NULL;
	Common::GameObject* pZombie = NULL;
	
	if (pGameObjectA == this->GetGameObject())
	{
		pZombie = pGameObjectA;
		
		std::string subNameB = (pGameObjectB->GetGUID()).substr(0,10);
		if (subNameB.compare("projectile") == 0)
			pProjectTile = pGameObjectB;
		
	}
	else if (pGameObjectB == this->GetGameObject())
	{
		pZombie = pGameObjectB;

		std::string subNameA = (pGameObjectA->GetGUID()).substr(0,10);
		if (subNameA.compare("projectile") == 0)
			pProjectTile = pGameObjectA;
	}

	if (pZombie)
	{
		if (pProjectTile)
		{
			m_bIsStunned = true;
			m_fStunTime = 0.0f;
		}
	}
}

