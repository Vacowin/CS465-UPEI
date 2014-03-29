#include "UtilityWorldState.h"
#include "Assignment4\ExampleGame\ComponentTimerLogic.h"
#include "Assignment4\ExampleGame\src\ExampleGame.h"
#include <vector>

UtilityWorldState::UtilityWorldState()
{
	m_sCoinID1 = "";
	m_sCoinID2 = "";
	m_pCharacter = nullptr;
	m_pZombieCharacter = nullptr;
	m_pZombieCoin1 = nullptr;
	m_pZombieCoin2 = nullptr;
}

UtilityWorldState::~UtilityWorldState()
{

}

void UtilityWorldState::ApplyAction(AIState p_eStateAction)
{
	m_eStateAction = p_eStateAction;
}

float UtilityWorldState::Utility(GameObject* p_pGameObject)
{
	float fUtility = 0.0;
	if (m_pZombieCharacter == nullptr)
	{
		m_pZombieCharacter = p_pGameObject;
		//fUtility = 100;
	}
	else if (m_pZombieCoin1 == nullptr)
	{
		m_pZombieCoin1 = p_pGameObject;
	}
	else if (m_pZombieCoin2 == nullptr)
	{
		m_pZombieCoin2 = p_pGameObject;
	}

	if (p_pGameObject == m_pZombieCharacter)
	{
		if (m_eStateAction == AIState::eAIState_Chasing)
			fUtility = 100;
		else if (m_eStateAction == AIState::eAIState_Wander)
			fUtility = 0;
		else if (m_eStateAction == AIState::eAIState_ChasingCoin)
			fUtility = 0;
	}
	else if (p_pGameObject == m_pZombieCoin1)
	{
		if (m_eStateAction == AIState::eAIState_Chasing)
			fUtility = 0;
		else if (m_eStateAction == AIState::eAIState_Wander)
			fUtility = 50;
		else if (m_eStateAction == AIState::eAIState_ChasingCoin)
		{
			if (m_sCoinID1.compare("") != 0)
			{
				fUtility = 100;
				ComponentAIController *pAIController = static_cast<ComponentAIController*>(p_pGameObject->GetComponent("GOC_AIController"));
				pAIController->SetCoinTarget(m_sCoinID1);
			}
		}
	}
	else if (p_pGameObject == m_pZombieCoin2)
	{
		if (m_eStateAction == AIState::eAIState_Chasing)
			fUtility = 0;
		else if (m_eStateAction == AIState::eAIState_Wander)
			fUtility = 50;
		else if (m_eStateAction == AIState::eAIState_ChasingCoin)
		{
			if (m_sCoinID2.compare("") != 0)
			{
				fUtility = 100;
				ComponentAIController *pAIController = static_cast<ComponentAIController*>(p_pGameObject->GetComponent("GOC_AIController"));
				pAIController->SetCoinTarget(m_sCoinID2);
			}
		}
	}

	return fUtility;
}

UtilityWorldState* UtilityWorldState::Copy()
{
	UtilityWorldState *worldStateCopy = new UtilityWorldState();

	GameObject* pTimer = ExampleGame::GetInstance()->GameObjectManager()->GetGameObject("timer");
	ComponentTimerLogic* pTimerLogic = static_cast<ComponentTimerLogic*>(pTimer->GetComponent("GOC_TimerLogic"));
	std::vector<std::string>* pListCoinID = pTimerLogic->GetCurrentCoinID();
	for (int j = 0; j<pListCoinID->size(); j++)
	{
		if (j == 0)
			worldStateCopy->m_sCoinID1 = pListCoinID->at(j);
		else if (j == 1)
			worldStateCopy->m_sCoinID2 = pListCoinID->at(j);
		else if (j==2)
			break;
	}

	worldStateCopy->m_pCharacter = ExampleGame::GetInstance()->GameObjectManager()->GetGameObject("character");
	worldStateCopy->m_pZombieCharacter = ExampleGame::GetInstance()->GameObjectManager()->GetGameObject("zombieCharacter");
	worldStateCopy->m_pZombieCoin1 = ExampleGame::GetInstance()->GameObjectManager()->GetGameObject("zombieCoin1");
	worldStateCopy->m_pZombieCoin2 = ExampleGame::GetInstance()->GameObjectManager()->GetGameObject("zombieCoin2");

	return worldStateCopy;
}