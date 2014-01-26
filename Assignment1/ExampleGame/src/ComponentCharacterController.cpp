//------------------------------------------------------------------------
// ComponentCharacterController
//
// Created:	2012/12/14
// Author:	Carel Boers
//	
// This class implements a character controller. It polls input and sends
// movement instructions to the relevant sibling components.
//------------------------------------------------------------------------

#include "W_Model.h"
#include "ComponentAnimController.h"
#include "ComponentCharacterController.h"
#include "ComponentRenderableMesh.h"
#include "GameObject.h"

using namespace week2;

//------------------------------------------------------------------------------
// Method:    ComponentCharacterController
// Returns:   
// 
// Constructor.
//------------------------------------------------------------------------------
ComponentCharacterController::ComponentCharacterController()
{
	memset(m_bKeysDown, 0, sizeof(bool) * 256);
	memset(m_bKeysDownLast, 0, sizeof(bool) * 256);

	m_fRotation = 0;
}

//------------------------------------------------------------------------------
// Method:    ~ComponentCharacterController
// Returns:   
// 
// Destructor.
//------------------------------------------------------------------------------
ComponentCharacterController::~ComponentCharacterController()
{
}

//------------------------------------------------------------------------------
// Method:    Update
// Parameter: float p_fDelta
// Returns:   void
// 
// Polls input and sends movement instructions to relevant sibling components.
//------------------------------------------------------------------------------
void ComponentCharacterController::Update(float p_fDelta)
{
	// Transfer previous frame key presses to "Last" array and get current keyboard state
	for (int i = 0; i < 256; ++i)
	{
		m_bKeysDownLast[i] = m_bKeysDown[i];
		m_bKeysDown[i] = (glfwGetKey(i) == GLFW_PRESS);
	}

	Common::Transform& transform = this->GetGameObject()->GetTransform();

	ComponentAnimController* pAnimation = static_cast<ComponentAnimController*>(this->GetGameObject()->GetComponent("GOC_AnimController"));

	if ((!m_bKeysDown['W'] || !m_bKeysDown['S'])&&(m_bKeysDownLast['W'] && !m_bKeysDown['W'] || m_bKeysDownLast['S'] && !m_bKeysDown['S']))
	{
        pAnimation->SetAnim("idle");
		if (m_bTurnBack == false)
		{
			m_bTurnBack = true;
		}
	}
    
	if ((m_bKeysDown['a'] || m_bKeysDown['A']))
	{
		transform.Rotate(glm::vec3(0.0f,200.0f*p_fDelta,0.0f));
		m_fRotation += 200.0f*p_fDelta;
	}
	else if ((m_bKeysDown['d'] || m_bKeysDown['D']))
	{
		transform.Rotate(glm::vec3(0.0f,-200.0f*p_fDelta,0.0f));
		m_fRotation -= 200.0f*p_fDelta;
	}

	float z1 = 9*cos((m_fRotation - 40) * PI / 180) - 9*sin((m_fRotation - 40) * PI / 180);
	float x1 = 9*sin((m_fRotation - 40) * PI / 180) + 9*cos((m_fRotation - 40) * PI / 180);

	if (glfwGetKey('W'))
	{
		transform.Translate(glm::vec3(x1*p_fDelta, 0, z1*p_fDelta));
        if (m_bKeysDown['W'] != m_bKeysDownLast['W'])
		    pAnimation->SetAnim("run");
	}
    else if (glfwGetKey('S') )
	{
		if (m_bTurnBack)
		{
			transform.Rotate(glm::vec3(0.0f,180,0.0f));
			m_fRotation += 180;
			m_bTurnBack = false;
		}

		transform.Translate(glm::vec3(x1*p_fDelta, 0, z1*p_fDelta));
        if (m_bKeysDown['S'] != m_bKeysDownLast['S'])
		    pAnimation->SetAnim("run");
	}
}
