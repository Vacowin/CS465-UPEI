//------------------------------------------------------------------------
// ComponentRenderableMesh
//
// Created:	2012/12/14
// Author:	Carel Boers
//	
// This class implements a component that is renderable.
//------------------------------------------------------------------------

#include "W_Model.h"
#include "ComponentRenderableMesh.h"
#include "GameObject.h"
#include "SceneManager.h"

using namespace week2;

//------------------------------------------------------------------------------
// Method:    ComponentRenderableMesh
// Returns:   
// 
// Constructor.
//------------------------------------------------------------------------------
ComponentRenderableMesh::ComponentRenderableMesh()
	:
	m_pModel(NULL)
{
}

//------------------------------------------------------------------------------
// Method:    ~ComponentRenderableMesh
// Returns:   
// 
// Destructor.
//------------------------------------------------------------------------------
ComponentRenderableMesh::~ComponentRenderableMesh()
{
	// Remove the model from the scene
	Common::SceneManager::Instance()->RemoveModel(m_pModel);

	// Delete the model
	if (m_pModel)
	{
		delete m_pModel;
		m_pModel = NULL;
	}
}


Common::ComponentBase* ComponentRenderableMesh::CreateComponent(TiXmlNode* p_pNode)
{
	assert(strcmp(p_pNode->Value(), "GOC_RenderableMesh") == 0);
	ComponentRenderableMesh* pMeshComponent = new ComponentRenderableMesh();

	std::string strModel, strTexture, strVertex, strFragment;

	// Iterate Anim elements in the XML
	TiXmlNode* pChildNode = p_pNode->FirstChild();
	while (pChildNode != NULL)
	{
		const char* szNodeName = pChildNode->Value();
		if (strcmp(szNodeName, "Model") == 0)
		{
			// Parse attributes
			TiXmlElement* pElement = pChildNode->ToElement();

			// Name
			const char* szPath = pElement->Attribute("path");
			if (szPath == NULL)
			{
				delete pMeshComponent;
				return NULL;
			}
			strModel = std::string(szPath);
		}

		if (strcmp(szNodeName, "Textures") == 0)
		{
			TiXmlElement* pElement = pChildNode->ToElement();
			const char* szPath = pElement->Attribute("path");
			if (szPath == NULL)
			{
				delete pMeshComponent;
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
				delete pMeshComponent;
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
				delete pMeshComponent;
				return NULL;
			}
			strFragment = std::string(szPath);
		}

		pChildNode = pChildNode->NextSibling();
	}

	pMeshComponent->Init(strModel, strTexture, strVertex, strFragment);

	return pMeshComponent;
}

//------------------------------------------------------------------------------
// Method:    Init
// Parameter: const std::string & p_strPath
// Parameter: const std::string & p_strTexturePath
// Parameter: const std::string & p_strVertexProgramPath
// Parameter: const std::string & p_strFragmentProgramPath
// Returns:   void
// 
// Initializes this component by loading the renderable object.
//------------------------------------------------------------------------------
void ComponentRenderableMesh::Init(const std::string& p_strPath, const std::string &p_strTexturePath, const std::string &p_strVertexProgramPath, const std::string &p_strFragmentProgramPath)
{
	m_pModel = new wolf::Model(p_strPath, p_strTexturePath, p_strVertexProgramPath, p_strFragmentProgramPath);
	Common::SceneManager::Instance()->AddModel(m_pModel);
}

//------------------------------------------------------------------------------
// Method:    SyncTransform
// Returns:   void
// 
// TODO: document me.
//------------------------------------------------------------------------------
void ComponentRenderableMesh::SyncTransform()
{
	m_pModel->SetTransform(this->GetGameObject()->GetTransform().GetTransformation());
}