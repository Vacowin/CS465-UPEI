//------------------------------------------------------------------------
// ComponentAIController
//
// Created:	2012/12/14
// Author:	Carel Boers
//	
// This class implements an AI controller. It loads a decision tree from
// XML and processes the game state to decide it's best state.
//------------------------------------------------------------------------

#ifndef COMPNENTAICONTROLLER_H
#define COMPNENTAICONTROLLER_H

#include "ComponentBase.h"
#include "StateMachine.h"
#include "tinyxml\tinyxml.h"

namespace week2
{
	enum AIState
	{
			eAIState_None = -1,
			eAIState_Wander = 0,
			eAIState_Idle,
			eAIState_Chasing,
			eAIState_ChasingCoin
	};
	class ComponentAIController : public Common::ComponentBase
	{
	public:
		//------------------------------------------------------------------------------
		// Public types.
		//------------------------------------------------------------------------------

		// Supported AI behaviours
		

	public:
		//------------------------------------------------------------------------------
		// Public methods.
		//------------------------------------------------------------------------------
		ComponentAIController();
		virtual ~ComponentAIController();

		static Common::ComponentBase* CreateComponent(TiXmlNode* p_pNode);

		virtual const std::string FamilyID() { return std::string("GOC_AIController"); }
		virtual const std::string ComponentID(){ return std::string("GOC_AIController"); }
		virtual void Update(float p_fDelta);

		virtual void Init();

		Common::StateMachine* GetStateMachine() { return m_pStateMachine; }

		// Mapping method
		AIState MapActionToState(const std::string& p_strAction)
		{
			if (p_strAction.compare("ACTION_CHASE") == 0)			{ return eAIState_Chasing; }
			else if (p_strAction.compare("ACTION_CHASECOIN") == 0)	{ return eAIState_ChasingCoin; }
			else if (p_strAction.compare("ACTION_WANDER") == 0)		{ return eAIState_Wander; }	
			else if (p_strAction.compare("ACTION_IDLE") == 0)		{ return eAIState_Idle; }	
			else													{ return eAIState_None; }
		}

		void SetCoinTarget(std::string p_sCoin) { m_sCoinTarget = p_sCoin;}
		const std::string& GetCoinTarget() { return m_sCoinTarget;}
		AIState GetCurrentState() { return (AIState)m_pStateMachine->GetCurrentStateID();}
	private:
		//------------------------------------------------------------------------------
		// Private members.
		//------------------------------------------------------------------------------


		// Our state machine
		Common::StateMachine* m_pStateMachine;

		std::string m_sCoinTarget;
		int m_iFrameCount;
	};
}

#endif // COMPNENTAICONTROLLER_H

