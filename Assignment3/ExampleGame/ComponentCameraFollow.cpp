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

Common::ComponentBase* ComponentCameraFollow::CreateComponent(TiXmlNode* p_pNode)
{
	assert(strcmp(p_pNode->Value(), "GOC_CameraFollow") == 0);

	float fFOV = 0.0f;
	float fAspectRatio = 0.0f;
	float fNearClip = 0.0f;
	float fFarClip = 0.0f;
	glm::vec3 vPosition, vTarget, vUp;

	TiXmlNode* pChildNode = p_pNode->FirstChild();
	while (pChildNode != NULL)
	{
		const char* szNodeName = pChildNode->Value();

		if (strcmp(szNodeName, "FOV") == 0)
		{
			TiXmlElement* pElement = pChildNode->ToElement();
			pElement->QueryFloatAttribute("value", &fFOV);
		}

		if (strcmp(szNodeName, "AspectRatio") == 0)
		{
			TiXmlElement* pElement = pChildNode->ToElement();
			pElement->QueryFloatAttribute("value", &fAspectRatio);
		}

		if (strcmp(szNodeName, "NearClip") == 0)
		{
			TiXmlElement* pElement = pChildNode->ToElement();
			pElement->QueryFloatAttribute("value", &fNearClip);
		}

		if (strcmp(szNodeName, "FarClip") == 0)
		{
			TiXmlElement* pElement = pChildNode->ToElement();
			pElement->QueryFloatAttribute("value", &fFarClip);
		}

		if (strcmp(szNodeName, "Position") == 0)
		{
			TiXmlElement* pElement = pChildNode->ToElement();
			pElement->QueryFloatAttribute("x", &vPosition.x);
			pElement->QueryFloatAttribute("y", &vPosition.y);
			pElement->QueryFloatAttribute("z", &vPosition.z);
		}

		if (strcmp(szNodeName, "Target") == 0)
		{
			TiXmlElement* pElement = pChildNode->ToElement();
			pElement->QueryFloatAttribute("x", &vTarget.x);
			pElement->QueryFloatAttribute("y", &vTarget.y);
			pElement->QueryFloatAttribute("z", &vTarget.z);
		}

		if (strcmp(szNodeName, "Up") == 0)
		{
			TiXmlElement* pElement = pChildNode->ToElement();
			pElement->QueryFloatAttribute("x", &vUp.x);
			pElement->QueryFloatAttribute("y", &vUp.y);
			pElement->QueryFloatAttribute("z", &vUp.z);
		}

		pChildNode = pChildNode->NextSibling();
	}

	return new ComponentCameraFollow(fFOV, fAspectRatio, fNearClip, fFarClip, vPosition, vTarget, vUp);
}

void ComponentCameraFollow::Update(float p_fDelta) 
{
	Common::Transform objectTransform = this->GetGameObject()->GetTransform();

	ComponentCharacterController *pControllerComponent = static_cast<ComponentCharacterController*>(GetGameObject()->GetComponent("GOC_CharacterController"));
	float fcharRotation = pControllerComponent->getCharacterRotation();

	//float z1 = 15*cos((fcharRotation - 40) * PI / 180) - 15*sin((fcharRotation - 40) * PI / 180);
	//float x1 = 15*sin((fcharRotation - 40) * PI / 180) + 15*cos((fcharRotation - 40) * PI / 180);

	float z1 = 15*cos((fcharRotation - 80) * PI / 180) - 15*sin((fcharRotation - 80) * PI / 180);
	float x1 = 15*sin((fcharRotation - 80) * PI / 180) + 15*cos((fcharRotation - 80) * PI / 180);

	m_pCamera->SetPos(objectTransform.GetTranslation() + glm::vec3(-x1 , 10.0f, -z1));
	m_pCamera->SetTarget(objectTransform.GetTranslation() + glm::vec3(0.0f, 6.0f, 0.0f));

}