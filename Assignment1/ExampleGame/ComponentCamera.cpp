#include "ComponentCamera.h"
#include "Transform.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "src\ComponentCharacterController.h"
#include "W_Types.h"

using namespace week2;

ComponentCamera::ComponentCamera(float p_fFOV, float p_fAspectRatio, float p_fNearClip, float p_fFarClip, const glm::vec3 &p_vPos, const glm::vec3& p_vTarget, const glm::vec3& p_vUp)
{
	m_pCamera = new Common::SceneCamera(p_fFOV, p_fAspectRatio, p_fNearClip, p_fFarClip, p_vPos, p_vTarget, p_vUp);
}


void ComponentCamera::Update(float p_fDelta) 
{
	Common::GameObject* pCharacter = this->GetGameObject()->GetManager()->GetGameObject("character");
	m_pCamera->SetTarget(pCharacter->GetTransform().GetTranslation());
}