//------------------------------------------------------------------------
// AIStateChasing
//
// Created:	2013/02/10
// Author:	Carel Boers
//	
// Idle behaviour state.
//------------------------------------------------------------------------

#include "AIPathfinder.h"
#include "AIStateChasingCoin.h"
#include "ComponentBase.h"
#include "Assignment4/ExampleGame/ComponentAIController.h"
#include "Assignment4/ExampleGame/src/ComponentAnimController.h"
#include "GameObject.h"
#include <glm/gtx/vector_angle.hpp>
#include <Windows.h>
#include "Assignment4\ExampleGame\ComponentZombieStun.h"

using namespace week2;

//------------------------------------------------------------------------------
// Method:    AIStateChasing
// Returns:   
// 
// Constructor.
//------------------------------------------------------------------------------
AIStateChasingCoin::AIStateChasingCoin()
{
}

//------------------------------------------------------------------------------
// Method:    ~AIStateChasing
// Returns:   
// 
// Destructor.
//------------------------------------------------------------------------------
AIStateChasingCoin::~AIStateChasingCoin()
{
}

//------------------------------------------------------------------------------
// Method:    Enter
// Returns:   void
// 
// Called when this state becomes active.
//------------------------------------------------------------------------------
void AIStateChasingCoin::Enter()
{
	// Trigger the walk animation
	ComponentAIController* pController = static_cast<ComponentAIController*>(m_pStateMachine->GetStateMachineOwner());
	Common::ComponentBase* pComponent = pController->GetGameObject()->GetComponent("GOC_AnimController");
	if (pComponent)
	{
		ComponentAnimController* pAnimController = static_cast<ComponentAnimController*>(pComponent);
		pAnimController->SetAnim("run");
	}

	//m_pTargetGameObject = pController->GetGameObject()->GetManager()->GetGameObject(pController->GetCoinTarget());
}

//------------------------------------------------------------------------------
// Method:    Update
// Parameter: float p_fDelta
// Returns:   void
// 
// Called each from when this state is active.
//------------------------------------------------------------------------------
void AIStateChasingCoin::Update(float p_fDelta)
{
	ComponentAIController* pController = static_cast<ComponentAIController*>(m_pStateMachine->GetStateMachineOwner());
	m_pTargetGameObject = pController->GetGameObject()->GetManager()->GetGameObject(pController->GetCoinTarget());

	if (m_pTargetGameObject)
	{
		ComponentAIController* pController = static_cast<ComponentAIController*>(m_pStateMachine->GetStateMachineOwner());
		Common::Transform& transform = pController->GetGameObject()->GetTransform();
		Common::Transform& targetTransform = m_pTargetGameObject->GetTransform();

		float fVelocity = 6.0f;
		ComponentZombieStun* pStunComponent = static_cast<ComponentZombieStun*>(pController->GetGameObject()->GetComponent("GOC_ZombieStun"));
		if (pStunComponent->GetIsStunned())
			fVelocity /= 2;

		bool m_bPathChange = false;
		glm::vec3 vTemp;
		// In two cases we want to recalculate our path:
		//	1. If we don't have a path
		//  2. If our target position is different from the existing path we are following
		if (m_lPath.empty())
		{
			// We don't have a path yet
			m_lPath = AIPathfinder::Instance()->FindPath(transform.GetTranslation(), targetTransform.GetTranslation());
		}
		else
		{
			const AIPathfinder::PathNode* const pEndNode = AIPathfinder::Instance()->GetClosestNode(targetTransform.GetTranslation());
			glm::vec3 vTarget = m_lPath.back();
			if (pEndNode->m_vPosition != vTarget)
			{
				// Our path has changed
				//m_lPath.pop_front();
				if (m_lPath.size()>1)
					vTemp = glm::vec3(static_cast<glm::vec3>(*(m_lPath.begin())));
				m_lPath = AIPathfinder::Instance()->FindPath(transform.GetTranslation(), targetTransform.GetTranslation());
				m_bPathChange = true;
			}
		}

		// Find the next node we should move towards
		glm::vec3 vMoveTarget = transform.GetTranslation();
		if (m_lPath.size() > 0)
		{
			
			AIPathfinder::PositionList::const_iterator it1;
			int i;
			glm::vec3 node2;
			for (it1 = m_lPath.begin(), i =0;it1!=m_lPath.end();it1++)
			{
				if (i==1)
				{
					node2 = static_cast<glm::vec3>(*it1);
					break;
				}
				i++;
			}
			
			// Move towards the first node in the path
			AIPathfinder::PositionList::const_iterator it = m_lPath.begin();
			
			vMoveTarget = static_cast<glm::vec3>(*it);
			
			if(m_bPathChange)
			{
				if (node2.x == vTemp.x && node2.z == vTemp.z)
				{
					//vMoveTarget = vTemp;
					if (m_lPath.size()>1)
					{
						m_lPath.pop_front();
						it = m_lPath.begin();
						vMoveTarget = static_cast<glm::vec3>(*it);
						printf("true\n");
					}
				}
				else
					printf("false %f %f   %f %f\n", node2.x, vTemp.x, node2.z, vTemp.z);
			}
			
			// If we're here then choose then next node instead
			if (m_lPath.size() > 1 && glm::length(vMoveTarget - transform.GetTranslation()) < 0.5f)
			{
				m_lPath.pop_front();
				it = m_lPath.begin();
				vMoveTarget = static_cast<glm::vec3>(*it);
			}
		}

		// Move towards our destination
		glm::vec3 vDiff = vMoveTarget - transform.GetTranslation();
		if (glm::length(vDiff) > 0.0f)
		{
			vDiff = glm::normalize(vDiff);
			transform.Translate(vDiff * fVelocity * p_fDelta);

			// Rotate facing direction
			float fAngle = glm::orientedAngle(glm::vec3(0.0f, 0.0f, 1.0f), vDiff, glm::vec3(0.0f, 1.0f, 0.0f));
			transform.SetRotationXYZ(0.0f, fAngle, 0.0f);
		}
	}
	else
	{
		// If we don't have a target, we shouldn't be in a chase state; go to idle
		m_pStateMachine->GoToState(eAIState_Idle);
	}
}

//------------------------------------------------------------------------------
// Method:    Exit
// Returns:   void
// 
// Called when this state becomes inactive.
//------------------------------------------------------------------------------
void AIStateChasingCoin::Exit()
{	
	m_pTargetGameObject = NULL;
}