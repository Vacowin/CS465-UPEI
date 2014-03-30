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
#include "Assignment4\ExampleGame\ComponentCamera.h"
#include "SceneManager.h"
#include "Assignment4\ExampleGame\ComponentRigidBody.h"
#include "Assignment4\ExampleGame\EventManager.h"
#include "Assignment4\ExampleGame\EventCharacterCollision.h"
#include "Assignment4\ExampleGame\EventObjectCollision.h"

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

	m_fRotateSpeed = 3;
	m_fSpeed = 20;
	m_numProjectiles = 0;
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


Common::ComponentBase* ComponentCharacterController::CreateComponent(TiXmlNode* p_pNode)
{
	assert(strcmp(p_pNode->Value(), "GOC_CharacterController") == 0);
	ComponentCharacterController* pCharacterControllerComponent = new ComponentCharacterController();

	return pCharacterControllerComponent;
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
	if (!m_bActive) return;
	// Transfer previous frame key presses to "Last" array and get current keyboard state
	for (int i = 0; i < 256; ++i)
	{
		m_bKeysDownLast[i] = m_bKeysDown[i];
		m_bKeysDown[i] = (glfwGetKey(i) == GLFW_PRESS);
	}

	ComponentAnimController* pAnimation = static_cast<ComponentAnimController*>(this->GetGameObject()->GetComponent("GOC_AnimController"));

	if ((!m_bKeysDown['W'] || !m_bKeysDown['S'])&&(m_bKeysDownLast['W'] && !m_bKeysDown['W'] || m_bKeysDownLast['S'] && !m_bKeysDown['S']))
	{
        pAnimation->SetAnim("idle");
		if (m_bTurnBack == false)
		{
			m_bTurnBack = true;
		}
	}

	ComponentRigidBody* pCharRigid = static_cast<ComponentRigidBody*>(this->GetGameObject()->GetComponent("GOC_RigidBody"));
	btRigidBody *m_pRigidBody = pCharRigid->GetRigidBody();
    m_pRigidBody->setAngularFactor(0);
	btTransform trans;
	m_pRigidBody->getMotionState()->getWorldTransform(trans);

	glm::quat qRot = glm::quat(trans.getRotation().getW(), trans.getRotation().getX(), trans.getRotation().getY(), trans.getRotation().getZ());
	m_vFace = glm::mat3_cast(qRot) * glm::vec3(-0.707,0,0.707);
	
	if (glfwGetKey('W') == GLFW_PRESS /* && !m_bMoveForwardToogle*/)
	{
		m_pRigidBody->setLinearVelocity(btVector3(m_vFace.x, 0, m_vFace.z)*m_fSpeed);
        if (m_bKeysDown['W'] != m_bKeysDownLast['W'])
		    pAnimation->SetAnim("run");
	}
	if (glfwGetKey('W') == GLFW_RELEASE)
	{
		m_pRigidBody->setLinearVelocity(btVector3(0.0f,0.0f,0.0f));
	}

	if (glfwGetKey('A') == GLFW_PRESS)
	{
		m_pRigidBody->setAngularVelocity(btVector3(0.0,m_fRotateSpeed,0.0));
		m_pRigidBody->setLinearVelocity(btVector3(0.0f,0.0f,0.0f));
	}
	else if (glfwGetKey('D') == GLFW_PRESS)
	{
		m_pRigidBody->setAngularVelocity(btVector3(0.0,-m_fRotateSpeed,0.0));
		m_pRigidBody->setLinearVelocity(btVector3(0.0f,0.0f,0.0f));
	}
	if (glfwGetKey('A') == GLFW_RELEASE && glfwGetKey('D') == GLFW_RELEASE)
	{
		m_pRigidBody->setAngularVelocity(btVector3(0.0f,0.0f,0.0f));
	}

    if (glfwGetKey('S') )
	{
		if (m_bTurnBack)
		{
			m_bTurnBack = false;
		}
		m_pRigidBody->setLinearVelocity(-btVector3(m_vFace.x, 0, m_vFace.z)*m_fSpeed);
        if (m_bKeysDown['S'] != m_bKeysDownLast['S'])
		    pAnimation->SetAnim("run");
	}

	// Switch camera
	if (glfwGetKey('C') == GLFW_PRESS && !m_bToggleCamera)
    {
		m_b3PCamera = !m_b3PCamera;
        m_bToggleCamera = true;
    }
    else if (glfwGetKey('C') == GLFW_RELEASE)
        m_bToggleCamera = false;

	Common::SceneCamera* pCamera;
	if (m_b3PCamera)
    {
		pCamera = static_cast<ComponentCamera*>(GetGameObject()->GetComponent("GOC_CameraFollow"))->GetCamera();
    }
    else
		pCamera = static_cast<ComponentCamera*>(GetGameObject()->GetManager()->GetGameObject("lamp")->GetComponent("GOC_Camera"))->GetCamera();
  
	Common::SceneManager::Instance()->AttachCamera(pCamera);

	if (!m_bToggleShoot && glfwGetMouseButton(0))
	{
		m_bToggleShoot = true;

		glm::vec3 offset = glm::vec3(m_vFace.x*2.5f,5.5,m_vFace.z*2.5f);
		glm::vec3 pos = this->GetGameObject()->GetTransform().GetTranslation();
		glm::vec3 vNewPos = pos + glm::vec3(offset.x, offset.y, offset.z);

		Common::GameObject* pProjectTile = this->GetGameObject()->GetManager()->CreateGameObject("Assignment4/ExampleGame/data/xml/projectile.xml");
		pProjectTile->GetManager()->SetGameObjectGUID(pProjectTile, "projectile" + std::to_string(m_numProjectiles++));
		pProjectTile->GetTransform().SetTranslation(glm::vec3(vNewPos.x,vNewPos.y,vNewPos.z));
		ComponentRigidBody* pComponentRigid = static_cast<ComponentRigidBody*>(pProjectTile->GetComponent("GOC_RigidBody"));
		pComponentRigid->BindGameObject();
		pComponentRigid->ApplyCentralImpulse(glm::vec3(offset.x * 40, 0.0f, offset.z*40));
	}
	else if (!glfwGetMouseButton(0))
		m_bToggleShoot = false;
}

