//------------------------------------------------------------------------
// ComponentAIController
//
// Created:	2012/12/14
// Author:	Carel Boers
//	
// This class implements an AI controller. It loads a decision tree from
// XML and processes the game state to decide it's best state.
//------------------------------------------------------------------------

#include "W_Model.h"
#include "Assignment4/ExampleGame/src/ComponentAnimController.h"
#include "Assignment4/ExampleGame/ComponentAIController.h"
#include "Assignment4/ExampleGame/src/ComponentRenderableMesh.h"
#include "GameObject.h"
#include "Assignment4\ExampleGame\AI\UtilityWorldState.h"

// AI States
#include "Assignment4/ExampleGame/AI/AIStateChasing.h"
#include "Assignment4/ExampleGame/AI/AIStateWander.h"
#include "Assignment4/ExampleGame/AI/AIStateIdle.h"
#include "Assignment4\ExampleGame\AI\AIStateChasingCoin.h"

#include "windows.h"

using namespace week2;

//------------------------------------------------------------------------------
// Method:    ComponentAIController
// Returns:   
// 
// Constructor.
//------------------------------------------------------------------------------
ComponentAIController::ComponentAIController()
	:
	m_pStateMachine(NULL)
{
	m_sCoinTarget = "";
	m_iFrameCount = 0;
}

//------------------------------------------------------------------------------
// Method:    ~ComponentAIController
// Returns:   
// 
// Destructor.
//------------------------------------------------------------------------------
ComponentAIController::~ComponentAIController()
{
	if (m_pStateMachine)
	{
		m_pStateMachine->SetStateMachineOwner(NULL);
		delete m_pStateMachine;
		m_pStateMachine = NULL;
	}
}

Common::ComponentBase* ComponentAIController::CreateComponent(TiXmlNode* p_pNode)
{
	assert(strcmp(p_pNode->Value(), "GOC_AIController") == 0);
	ComponentAIController* pAIController = new ComponentAIController();
	pAIController->Init();

	return pAIController;
}

//------------------------------------------------------------------------------
// Method:    Update
// Parameter: float p_fDelta
// Returns:   void
// 
// Polls input and sends movement instructions to relevant sibling components.
//------------------------------------------------------------------------------
void ComponentAIController::Update(float p_fDelta)
{
	
	float bestUtility = 0;
	AIState bestState = eAIState_Wander;
	
	UtilityWorldState* worldStateCopy = UtilityWorldState::Copy();
	
	worldStateCopy->ApplyAction(AIState::eAIState_Chasing);
	float chasingUtility = worldStateCopy->Utility(this->GetGameObject());
	if (chasingUtility > bestUtility)
	{
		bestUtility = chasingUtility;
		bestState = eAIState_Chasing;
	}
	
	worldStateCopy->ApplyAction(eAIState_ChasingCoin);
	float chasingCoinUtility = worldStateCopy->Utility(this->GetGameObject());
	if (chasingCoinUtility > bestUtility)
	{
		bestUtility = chasingCoinUtility;
		bestState = eAIState_ChasingCoin;
	}
	
	worldStateCopy->ApplyAction(eAIState_Wander);
	float wanderUtility = worldStateCopy->Utility(this->GetGameObject());
	if (wanderUtility > bestUtility)
	{
		bestUtility = wanderUtility;
		bestState = eAIState_Wander;
	}
	
	if (m_pStateMachine->GetCurrentStateID() != bestState)
	{
		m_pStateMachine->GoToState(bestState);
	}
	
	m_pStateMachine->Update(p_fDelta);
	
}

//------------------------------------------------------------------------------
// Method:    Init
// Parameter: const char * p_strDecisionTreePath
// Returns:   void
// 
// Initializes the AI controller using a decision tree defined in XML.
//------------------------------------------------------------------------------
void ComponentAIController::Init()
{
	// Initialize the StateMachine and supported states
	m_pStateMachine = new Common::StateMachine();
	m_pStateMachine->SetStateMachineOwner(this);
	m_pStateMachine->RegisterState(eAIState_Wander, new AIStateWander());
	m_pStateMachine->RegisterState(eAIState_Idle, new AIStateIdle());
	m_pStateMachine->RegisterState(eAIState_Chasing, new AIStateChasing());
	m_pStateMachine->RegisterState(eAIState_ChasingCoin, new AIStateChasingCoin());
	//m_pStateMachine->GoToState(eAIState_Wander);
}
