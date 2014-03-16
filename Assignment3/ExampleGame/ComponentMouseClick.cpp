#include "ComponentMouseClick.h"
#include <GL/glfw.h>
#include "common\GameObject.h"
#include "glm\glm.hpp"
#include "common\Transform.h"

using namespace week2;

ComponentMouseClick::ComponentMouseClick()
{
	m_bIsClicked = false;
}


ComponentMouseClick::~ComponentMouseClick()
{
}

Common::ComponentBase* ComponentMouseClick::CreateComponent(TiXmlNode* p_pNode)
{
	assert(strcmp(p_pNode->Value(), "GOC_MouseClick") == 0);
	ComponentMouseClick* pComponent = new ComponentMouseClick();

	// Iterate elements in the XML
	TiXmlNode* pChildNode = p_pNode->FirstChild();
	while (pChildNode != NULL)
	{
		const char* szNodeName = pChildNode->Value();
		if (strcmp(szNodeName, "Width") == 0)
		{
			// Parse attributes
			TiXmlElement* pElement = pChildNode->ToElement();

			const char* szValue = pElement->Attribute("value");
			if (szValue == NULL)
			{
				delete pComponent;
				return NULL;
			}
			
			float fValue = atof(szValue);
			pComponent->SetWidth(fValue);
		}

		else if (strcmp(szNodeName, "Height") == 0)
		{
			// Parse attributes
			TiXmlElement* pElement = pChildNode->ToElement();

			const char* szValue = pElement->Attribute("value");
			if (szValue == NULL)
			{
				delete pComponent;
				return NULL;
			}
			
			float fValue = atof(szValue);
			pComponent->SetHeight(fValue);
		}

		pChildNode = pChildNode->NextSibling();
	}

	return pComponent;
}

void ComponentMouseClick::Update(float p_fDelta)
{
	if (!m_bActive)
	{
		m_bIsClicked = false;
		return;
	}

	Common::GameObject* pGO = this->GetGameObject();
	glm::vec3 pos = pGO->GetTransform().GetTranslation();

	int iButton = glfwGetMouseButton(0);
	if (iButton && !m_bToogleClick)
	{
		m_bToogleClick = true;
		int x, y = 0;
		glfwGetMousePos(&x, &y);

		if (x > pos.x && x < (pos.x + m_fWidth))
		{
			if (y > pos.y && y < pos.y + m_fHeight)
			{
				m_bIsClicked = true;
			}
		}
	}
	else if (!glfwGetMouseButton(0))
	{
		m_bToogleClick = false;
		m_bIsClicked = false;
	}
}