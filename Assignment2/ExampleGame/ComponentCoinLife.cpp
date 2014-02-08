#include "ComponentCoinLife.h"
#include "GameObject.h"
#include "EventCoinDisappeared.h"
#include "EventManager.h"

using namespace week2;


Common::ComponentBase* ComponentCoinLife::CreateComponent(TiXmlNode* p_pNode)
{
	assert(strcmp(p_pNode->Value(), "GOC_LifeSpan") == 0);
	ComponentCoinLife* pScoreComponent = new ComponentCoinLife();

	// Iterate elements in the XML
	TiXmlNode* pChildNode = p_pNode->FirstChild();
	while (pChildNode != NULL)
	{
		const char* szNodeName = pChildNode->Value();
		if (strcmp(szNodeName, "Timer") == 0)
		{
			// Parse attributes
			TiXmlElement* pElement = pChildNode->ToElement();

			const char* szValue = pElement->Attribute("value");
			if (szValue == NULL)
			{
				delete pScoreComponent;
				return NULL;
			}
			
			float iValue = atof(szValue);
			pScoreComponent->SetLifeSpan(iValue);
		}

		pChildNode = pChildNode->NextSibling();
	}

	return pScoreComponent;
}

void ComponentCoinLife::Update(float p_fDelta)
{
	if (abs(m_fTimePassed) > 1000) m_fTimePassed = 0.0f; 
	m_fTimePassed += p_fDelta;
	if (m_fTimePassed > m_fLifeSpan)
	{
		this->GetGameObject()->GetManager()->AddRemovedObject(this->GetGameObject());
		EventManager::Instance()->QueueEvent(new EventCoinDisappeared(this->GetGameObject()));
	}
}