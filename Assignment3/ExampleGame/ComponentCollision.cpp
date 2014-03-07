#include "ComponentCollision.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include <algorithm>
#include "EventManager.h"
#include "EventObjectCollision.h"

using namespace week2;
using namespace std;

Common::ComponentBase* ComponentCollision::CreateComponent(TiXmlNode* p_pNode)
{
	assert(strcmp(p_pNode->Value(), "GOC_CollisionSphere") == 0);
	ComponentCollision* pCollisionComponent = new ComponentCollision();

	// Iterate elements in the XML
	TiXmlNode* pChildNode = p_pNode->FirstChild();
	while (pChildNode != NULL)
	{
		const char* szNodeName = pChildNode->Value();
		if (strcmp(szNodeName, "Radius") == 0)
		{
			// Parse attributes
			TiXmlElement* pElement = pChildNode->ToElement();

			const char* szValue = pElement->Attribute("value");
			if (szValue == NULL)
			{
				delete pCollisionComponent;
				return NULL;
			}
			
			float fValue = atof(szValue);
			pCollisionComponent->SetRadius(fValue);
		}

		pChildNode = pChildNode->NextSibling();
	}

	return pCollisionComponent;
}


void ComponentCollision::Update(float p_fDelta)
{

}