#include "ComponentRenderableSquare.h"
#include "GameObject.h"


Common::ComponentBase* ComponentRenderableSquare::CreateComponent(TiXmlNode* p_pNode)
{
	assert(strcmp(p_pNode->Value(), "GOC_RenderableSquare") == 0);
	ComponentRenderableSquare* pSquareComponent = new ComponentRenderableSquare();

	std::string strTexture, strVertex, strFragment;
	float x,y,z;

	// Iterate Anim elements in the XML
	TiXmlNode* pChildNode = p_pNode->FirstChild();
	while (pChildNode != NULL)
	{
		const char* szNodeName = pChildNode->Value();

		if (strcmp(szNodeName, "Textures") == 0)
		{
			TiXmlElement* pElement = pChildNode->ToElement();
			const char* szPath = pElement->Attribute("path");
			if (szPath == NULL)
			{
				delete pSquareComponent;
				return NULL;
			}
			strTexture = std::string(szPath);
		}

		if (strcmp(szNodeName, "VertexProgram") == 0)
		{
			TiXmlElement* pElement = pChildNode->ToElement();
			const char* szPath = pElement->Attribute("path");
			if (szPath == NULL)
			{
				delete pSquareComponent;
				return NULL;
			}
			strVertex = std::string(szPath);
		}

		if (strcmp(szNodeName, "FragmentProgram") == 0)
		{
			TiXmlElement* pElement = pChildNode->ToElement();
			const char* szPath = pElement->Attribute("path");
			if (szPath == NULL)
			{
				delete pSquareComponent;
				return NULL;
			}
			strFragment = std::string(szPath);
		}

		if (strcmp(szNodeName, "Position") == 0)
		{
			// Parse attributes
			TiXmlElement* pElement = pChildNode->ToElement();

			if (pElement->QueryFloatAttribute("x", &x) != TIXML_SUCCESS)
			{
				delete pSquareComponent;
				return NULL;
			}

			if (pElement->QueryFloatAttribute("y", &y) != TIXML_SUCCESS)
			{
				delete pSquareComponent;
				return NULL;
			}

			if (pElement->QueryFloatAttribute("z", &z) != TIXML_SUCCESS)
			{
				delete pSquareComponent;
				return NULL;
			}

		}
		pChildNode = pChildNode->NextSibling();
	}

	pSquareComponent->Init(strTexture, strVertex, strFragment,x,y,z);

	return pSquareComponent;
}

void ComponentRenderableSquare::Init(const std::string &p_strTexturePath, const std::string &p_strVertexProgramPath, const std::string &p_strFragmentProgramPath,float x, float y, float z)
{
	m_pSquare = new Common::Square(p_strTexturePath, p_strVertexProgramPath, p_strFragmentProgramPath,x,y,z);
	Common::SceneManager::Instance()->AddSquareTexture(m_pSquare);
}

void ComponentRenderableSquare::SyncTransform()
{
	m_pSquare->SetTransform(this->GetGameObject()->GetTransform().GetTransformation());
}