#include "ComponentCoinMovement.h"
#include "Transform.h"
#include "GameObject.h"

using namespace week2;


Common::ComponentBase* ComponentCoinMovement::CreateComponent(TiXmlNode* p_pNode)
{
	assert(strcmp(p_pNode->Value(), "GOC_CoinMovement") == 0);
	ComponentCoinMovement* pMovementComponent = new ComponentCoinMovement();

	TiXmlNode* pChildNode = p_pNode->FirstChild();
	while (pChildNode != NULL)
	{
		const char* szNodeName = pChildNode->Value();
		if (strcmp(szNodeName, "RotationSpeed") == 0)
		{
			// Parse attributes
			TiXmlElement* pElement = pChildNode->ToElement();

			const char* szValue = pElement->Attribute("value");
			if (szValue == NULL)
			{
				delete pMovementComponent;
				return NULL;
			}

			float fValue = atof(szValue);
			pMovementComponent->SetRotationSpeed(fValue);
		}

		if (strcmp(szNodeName, "BobScale") == 0)
		{
			// Parse attributes
			TiXmlElement* pElement = pChildNode->ToElement();

			const char* szValue = pElement->Attribute("value");
			if (szValue == NULL)
			{
				delete pMovementComponent;
				return NULL;
			}

			float fValue = atof(szValue);
			pMovementComponent->SetBobScale(fValue);
		}

		pChildNode = pChildNode->NextSibling();
	}

	return pMovementComponent;
}


void ComponentCoinMovement::Update(float p_fDelta)
{
	if (!m_bActive) return;
	if (abs(p_fDelta) > 1000) p_fDelta = 0.0f; 


	Common::GameObject *pCoin = this->GetGameObject();
	Common::Transform& transform = pCoin->GetTransform();
	glm::vec3 translation = transform.GetTranslation();
	

	m_fBob = m_iBobFlag * p_fDelta*10;
	
	transform.Rotate(glm::vec3(0.0f, p_fDelta*m_fRotate, 0.0f));
	transform.Translate(glm::vec3(0.0f, m_fBob, 0.0f));

	if (transform.GetTranslation().y > 3+m_fBobScale ) 
	{	m_iBobFlag = -1;
		transform.SetTranslation(glm::vec3(translation.x, 3+m_fBobScale, translation.z));
	}
	else if (transform.GetTranslation().y < 3.0f) 
	{
		m_iBobFlag = 1;
		transform.SetTranslation(glm::vec3(translation.x, 3.0f, translation.z));
	}
}