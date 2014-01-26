#include "ComponentCamera.h"
#include "Transform.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "src\ComponentCharacterController.h"
#include "W_Types.h"

using namespace week2;

ComponentCamera::ComponentCamera()
{
	m_pCamera = new Common::SceneCamera(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f, glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f,5.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
}

void ComponentCamera::SetCamera(Common::SceneCamera* p_pCamera)
{
	m_pCamera = p_pCamera;
}

void ComponentCamera::Update(float p_fDelta) 
{
	Common::Transform objectTransform = this->GetGameObject()->GetTransform();
	if (this->GetGameObject()->GetGUID() == "character")
	{
		ComponentCharacterController *pControllerComponent = static_cast<ComponentCharacterController*>(GetGameObject()->GetComponent("GOC_CharacterController"));
		float fcharRotation = pControllerComponent->getCharacterRotation();

		float z1 = 15*cos((fcharRotation - 40) * PI / 180) - 15*sin((fcharRotation - 40) * PI / 180);
		float x1 = 15*sin((fcharRotation - 40) * PI / 180) + 15*cos((fcharRotation - 40) * PI / 180);

		m_pCamera->SetPos(objectTransform.GetTranslation() + glm::vec3(-x1 , 10.0f, -z1));
		m_pCamera->SetTarget(objectTransform.GetTranslation() + glm::vec3(0.0f, 6.0f, 0.0f));
	}
	else if (this->GetGameObject()->GetGUID() == "lamp")
	{
		Common::GameObject* pCharacter = this->GetGameObject()->GetManager()->GetGameObject("character");
		m_pCamera->SetTarget(pCharacter->GetTransform().GetTranslation());
	}
}