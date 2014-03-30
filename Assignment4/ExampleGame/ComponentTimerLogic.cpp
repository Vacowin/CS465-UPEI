#include "ComponentTimerLogic.h"
#include "GameObjectManager.h"
#include "assignment4/ExampleGame/ComponentCoinMovement.h"
#include "assignment4/ExampleGame/ComponentCollision.h"
#include "assignment4/ExampleGame/ComponentCoinLife.h"
#include "assignment4/ExampleGame/ComponentCoinScore.h"
#include "assignment4/ExampleGame/src/ComponentRenderableMesh.h"
#include <algorithm>
#include "EventObjectCollision.h"
#include "EventCoinDisappeared.h"
#include "EventCoinSpawned.h"
#include "EventCoinCollected.h"
#include "Assignment4\ExampleGame\ComponentRigidBody.h"
#include "Assignment4\ExampleGame\src\ExampleGame.h"

using namespace week2;

ComponentTimerLogic::ComponentTimerLogic()
{
	EventListener eventListener1 = std::tr1::bind(&ComponentTimerLogic::HandleCoinCollision, this, std::tr1::placeholders::_1);
	EventManager::Instance()->AddListener(Event_ObjectCollision, eventListener1);

	EventListener eventListener2 = std::tr1::bind(&ComponentTimerLogic::HandleCoinDisappeared, this, std::tr1::placeholders::_1);
	EventManager::Instance()->AddListener(Event_CoinDisappeared, eventListener2);

	m_lNumCoin = 0;
}

Common::ComponentBase* ComponentTimerLogic::CreateComponent(TiXmlNode* p_pNode)
{
	assert(strcmp(p_pNode->Value(), "GOC_TimerLogic") == 0);
	ComponentTimerLogic* pTimerComponent = new ComponentTimerLogic();

	TiXmlNode* pChildNode = p_pNode->FirstChild();
	while (pChildNode != NULL)
	{
		const char* szNodeName = pChildNode->Value();
		if (strcmp(szNodeName, "MaxObject") == 0)
		{
			// Parse attributes
			TiXmlElement* pElement = pChildNode->ToElement();

			const char* szValue = pElement->Attribute("value");
			if (szValue == NULL)
			{
				delete pTimerComponent;
				return NULL;
			}

			int iValue = atoi(szValue);
			pTimerComponent->SetMaxCoin(iValue);
		}

		if (strcmp(szNodeName, "Frequency") == 0)
		{
			// Parse attributes
			TiXmlElement* pElement = pChildNode->ToElement();

			const char* szValue = pElement->Attribute("value");
			if (szValue == NULL)
			{
				delete pTimerComponent;
				return NULL;
			}

			float fValue = atof(szValue);
			pTimerComponent->SetFrequency(fValue);
		}

		if (strcmp(szNodeName, "DefaultObject") == 0)
		{
			// Parse attributes
			TiXmlElement* pElement = pChildNode->ToElement();

			const char* szValue = pElement->Attribute("value");
			if (szValue == NULL)
			{
				delete pTimerComponent;
				return NULL;
			}

			std::string sValue = szValue;
			pTimerComponent->SetDefaultObject(sValue);
		}

		pChildNode = pChildNode->NextSibling();
	}

	return pTimerComponent;
}

void ComponentTimerLogic::Update(float p_fDelta)
{
	if (!m_bActive) return;

	if (abs(m_fTimePassed) > 1000) m_fTimePassed = 0.0f; 
	m_fTimePassed += p_fDelta;
	if (m_fTimePassed > m_fFrequency)
	{
		m_fTimePassed = 0.0f;
		if (m_lCoinList.size() < m_iMaxNumCoin)
		{
			CreateCoin();
		}
	}
}

void ComponentTimerLogic::CreateCoin()
{
	float randomX = rand()%20 -rand()%40;
	float randomZ = rand()%20 -rand()%40;;
	
	Common::GameObject* pCoin = ExampleGame::GetInstance()->GameObjectManager()->CreateGameObject("Assignment4/ExampleGame/data/xml/coin.xml");
	pCoin->GetManager()->SetGameObjectGUID(pCoin, "coin" + std::to_string(m_lNumCoin++));
	pCoin->GetTransform().Translate(glm::vec3(randomX, 10.0f, randomZ));
	m_lCoinList.push_back(pCoin);

	ComponentRigidBody* pCoinRigid = static_cast<ComponentRigidBody*>(pCoin->GetComponent("GOC_RigidBody"));
	pCoinRigid->BindGameObject();

	EventManager::Instance()->QueueEvent(new EventCoinSpawned(pCoin));
}

void ComponentTimerLogic::HandleCoinCollision(BaseEvent *p_Event)
{
	EventObjectCollision *pEventCollision = static_cast<EventObjectCollision*>(p_Event);
	Common::GameObject* pGameObjectA = pEventCollision->GetGameObject1();
	Common::GameObject* pGameObjectB = pEventCollision->GetGameObject2();
	
	Common::GameObject* pCharacter = NULL;
	Common::GameObject* pCoin = NULL;
	Common::GameObject* pZombie = NULL;
	
	std::string subName1 = (pGameObjectA->GetGUID()).substr(0,4);
	std::string subName2 = (pGameObjectB->GetGUID()).substr(0,4);

	if (subName1.compare("coin") == 0)
	{
		pCoin = pGameObjectA;
		if (pGameObjectB->GetGUID().compare("character") == 0)
			pCharacter = pGameObjectB;
		else
		{
			std::string subNameB = (pGameObjectB->GetGUID()).substr(0,6);
			if (subNameB.compare("zombie") == 0)
				pZombie = pGameObjectB;
		}
	}
	else if (subName2.compare("coin") == 0)
	{
		pCoin = pGameObjectB;
		if (pGameObjectA->GetGUID().compare("character") == 0)
			pCharacter = pGameObjectA;
		else
		{
			std::string subNameA = (pGameObjectA->GetGUID()).substr(0,6);
			if (subNameA.compare("zombie") == 0)
				pZombie = pGameObjectA;
		}
	}
	/*
	if (pGameObjectA->GetGUID().compare("character") == 0)
	{
		pCharacter = pGameObjectA;
		pOtherObject = pGameObjectB;
	}
	else if (pGameObjectB->GetGUID().compare("character") == 0)
	{
		pCharacter = pGameObjectB;
		pOtherObject = pGameObjectA;
	}
	else 	
	{
		std::string subName1 = (pGameObjectA->GetGUID()).substr(0,6);
		std::string subName2 = (pGameObjectB->GetGUID()).substr(0,6);
		if (subName1.compare("zombie") == 0)
		{
			pZombie = pGameObjectA;
			pOtherObject = pGameObjectB;
		}
		else if (subName2.compare("zombie") == 0)
		{
			pZombie = pGameObjectB;
			pOtherObject = pGameObjectA;
		}
	}
	*/

	if (pCoin)
	{
		if (pCharacter)
		{
			std::vector<Common::GameObject*>::iterator it = std::find(m_lCoinList.begin(), m_lCoinList.end(), pCoin);
			if (it != m_lCoinList.end())
			{
				m_lCoinList.erase(it);
			}	
			if (!this->GetGameObject()->GetManager()->CheckRemoveObject(pCoin))
				this->GetGameObject()->GetManager()->AddRemovedObject(pCoin);

			EventManager::Instance()->QueueEvent(new EventCoinCollected(pEventCollision->GetGameObject1(), pCoin));
			m_fTimePassed = 0.0f;
		}
		else if (pZombie)
		{
			std::vector<Common::GameObject*>::iterator it = std::find(m_lCoinList.begin(), m_lCoinList.end(), pCoin);
			if (it != m_lCoinList.end())
			{
				m_lCoinList.erase(it);
			}	
			if (!this->GetGameObject()->GetManager()->CheckRemoveObject(pCoin))
				this->GetGameObject()->GetManager()->AddRemovedObject(pCoin);
		
			m_fTimePassed = 0.0f;
		}
	}
}

void ComponentTimerLogic::HandleCoinDisappeared(BaseEvent *p_Event)
{
	EventCoinDisappeared *pEventCollision = static_cast<EventCoinDisappeared*>(p_Event);
	Common::GameObject *pCoin = pEventCollision->GetCoin();

	std::vector<Common::GameObject*>::iterator it = std::find(m_lCoinList.begin(), m_lCoinList.end(), pCoin);
	if (it != m_lCoinList.end())
	{
		m_lCoinList.erase(it);
	}	

	m_fTimePassed = 0.0f;
}

void ComponentTimerLogic::SetActive(bool value)
{
	m_bActive = value;
	for (int i=0;i<m_lCoinList.size();i++)
	{
		Common::GameObject* pCoin =m_lCoinList.at(i);
		ComponentCoinMovement* pMovement = static_cast<ComponentCoinMovement*>(pCoin->GetComponent("GOC_CoinMovement"));
		pMovement->SetActive(value);

		ComponentCoinLife* pLife = static_cast<ComponentCoinLife*>(pCoin->GetComponent("GOC_LifeSpan"));
		pLife->SetActive(value);
	}
}

vector<std::string>* ComponentTimerLogic::GetCurrentCoinID()
{
	vector<std::string>* pCoinIDList = new vector<std::string>();
	for (int i=0;i<m_lCoinList.size();i++)
		pCoinIDList->push_back(m_lCoinList.at(i)->GetGUID());

	return pCoinIDList;
}