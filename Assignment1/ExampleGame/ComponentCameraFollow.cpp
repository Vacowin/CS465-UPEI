#include "ComponentCameraFollow.h"
#include "Transform.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "src\ComponentCharacterController.h"
#include "W_Types.h"

using namespace week2;

ComponentCameraFollow::ComponentCameraFollow(float p_fFOV, float p_fAspectRatio, float p_fNearClip, float p_fFarClip, const glm::vec3 &p_vPos, const glm::vec3& p_vTarget, const glm::vec3& p_vUp)
{
	m_pCamera = new Common::SceneCamera(p_fFOV, p_fAspectRatio, p_fNearClip, p_fFarClip, p_vPos, p_vTarget, p_vUp);
}

void ComponentCameraFollow::Update(float p_fDelta) 
{
	Common::Transform objectTransform = this->GetGameObject()->GetTransform();

	ComponentCharacterController *pControllerComponent = static_cast<ComponentCharacterController*>(GetGameObject()->GetComponent("GOC_CharacterController"));
	float fcharRotation = pControllerComponent->getCharacterRotation();

	float z1 = 15*cos((fcharRotation - 40) * PI / 180) - 15*sin((fcharRotation - 40) * PI / 180);
	float x1 = 15*sin((fcharRotation - 40) * PI / 180) + 15*cos((fcharRotation - 40) * PI / 180);

	m_pCamera->SetPos(objectTransform.GetTranslation() + glm::vec3(-x1 , 10.0f, -z1));
	m_pCamera->SetTarget(objectTransform.GetTranslation() + glm::vec3(0.0f, 6.0f, 0.0f));

}