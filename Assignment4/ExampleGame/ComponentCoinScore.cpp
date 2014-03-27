#include "ComponentCoinScore.h"

using namespace week2;

void ComponentCoinScore::SetScore(int p_iScore)
{	
	m_iScore = p_iScore;
}

Common::ComponentBase* ComponentCoinScore::CreateComponent(TiXmlNode* p_pNode)
{
	assert(strcmp(p_pNode->Value(), "GOC_CoinScore") == 0);
	ComponentCoinScore* pScoreComponent = new ComponentCoinScore();

	// Iterate Anim elements in the XML
	TiXmlNode* pChildNode = p_pNode->FirstChild();
	while (pChildNode != NULL)
	{
		const char* szNodeName = pChildNode->Value();
		if (strcmp(szNodeName, "Score") == 0)
		{
			// Parse attributes
			TiXmlElement* pElement = pChildNode->ToElement();

			const char* szValue = pElement->Attribute("value");
			if (szValue == NULL)
			{
				delete pScoreComponent;
				return NULL;
			}
			std::string str = std::string(szValue);
			int iValue = atoi(szValue);
			pScoreComponent->SetScore(iValue);
		}

		pChildNode = pChildNode->NextSibling();
	}

	return pScoreComponent;
}