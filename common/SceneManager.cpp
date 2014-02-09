//------------------------------------------------------------------------
// SceneManager
//
// Created:	2012/12/23
// Author:	Carel Boers
//	
// A simple scene manager to manage our models and camera.
//------------------------------------------------------------------------

#include "SceneManager.h"

#include <algorithm>

using namespace Common;

// Static singleton instance
SceneManager* SceneManager::s_pSceneManagerInstance = NULL;

//------------------------------------------------------------------------------
// Method:    CreateInstance
// Returns:   void
// 
// Creates the singletone instance.
//------------------------------------------------------------------------------
void SceneManager::CreateInstance()
{
	assert(s_pSceneManagerInstance == NULL);
	s_pSceneManagerInstance = new SceneManager();
}

//------------------------------------------------------------------------------
// Method:    DestroyInstance
// Returns:   void
// 
// Destroys the singleton instance.
//------------------------------------------------------------------------------
void SceneManager::DestroyInstance()
{
	assert(s_pSceneManagerInstance != NULL);
	delete s_pSceneManagerInstance;
	s_pSceneManagerInstance = NULL;
}

//------------------------------------------------------------------------------
// Method:    Instance
// Returns:   SceneManager::SceneManager*
// 
// Access to singleton instance.
//------------------------------------------------------------------------------
SceneManager* SceneManager::Instance()
{
	assert(s_pSceneManagerInstance);
	return s_pSceneManagerInstance;
}

//------------------------------------------------------------------------------
// Method:    SceneManager
// Returns:   
// 
// Constructor.
//------------------------------------------------------------------------------
SceneManager::SceneManager()
	:
	m_pCamera(NULL),
	m_pLight(NULL)
{
	m_pLight = new DirectionalLight();
	m_pLight->m_diffuse = wolf::Color4(1.0f,1.0f,1.0f,1.0f);
	m_pLight->m_ambient = wolf::Color4(0.3f,0.3f,0.3f,1.0f);
	m_pLight->m_specular = wolf::Color4(1.0f,1.0f,1.0f,1.0f);
	m_pLight->m_vDirection = glm::vec3(0.0f,-1.0f,1.0f);
}

//------------------------------------------------------------------------------
// Method:    ~SceneManager
// Returns:   
// 
// Destructor.
//------------------------------------------------------------------------------
SceneManager::~SceneManager()
{
	if (m_pLight)
	{
		delete m_pLight;
		m_pLight = NULL;
	}
}

//------------------------------------------------------------------------------
// Method:    AddModel
// Parameter: wolf::Model * p_pModel
// Returns:   void
// 
// Adds a model the scene manager.
//------------------------------------------------------------------------------
void SceneManager::AddModel(wolf::Model* p_pModel)
{
	m_lModelList.push_back(p_pModel);
}


void SceneManager::AddSquareTexture(Square* p_pSquare)
{
	m_lSquareList.push_back(p_pSquare);
}

//------------------------------------------------------------------------------
// Method:    RemoveModel
// Parameter: wolf::Model * p_pModel
// Returns:   void
// 
// Removes a model from the scene manager.
//------------------------------------------------------------------------------
void SceneManager::RemoveModel(wolf::Model* p_pModel)
{
	ModelList::iterator it = std::find(m_lModelList.begin(), m_lModelList.end(), p_pModel);
	if (it != m_lModelList.end())
	{
		m_lModelList.erase(it);
	}	
}


void SceneManager::RemoveSquareTexture(Square* p_pSquare)
{
	SquareTextureList::iterator it = std::find(m_lSquareList.begin(), m_lSquareList.end(), p_pSquare);
	if (it != m_lSquareList.end())
	{
		m_lSquareList.erase(it);
	}	
}

void SceneManager::ClearSquareTexure()
{
	m_lSquareList.clear();
}
//------------------------------------------------------------------------------
// Method:    Clear
// Returns:   void
// 
// Clears the list of models in the scene manager.
//------------------------------------------------------------------------------
void SceneManager::Clear()
{
	m_lModelList.clear();
}

//------------------------------------------------------------------------------
// Method:    AddSprite
// Parameter: wolf::Sprite * p_pSprite
// Returns:   void
// 
// Adds the given sprite to the scene manager.
//------------------------------------------------------------------------------
void SceneManager::AddSprite(wolf::Sprite* p_pSprite)
{
	m_lSpriteList.push_back(p_pSprite);
}

//------------------------------------------------------------------------------
// Method:    RemoveSprite
// Parameter: wolf::Sprite * p_pSprite
// Returns:   void
// 
// Removes the given sprite from the scene manager.
//------------------------------------------------------------------------------
void SceneManager::RemoveSprite(wolf::Sprite* p_pSprite)
{
	SpriteList::iterator it = std::find(m_lSpriteList.begin(), m_lSpriteList.end(), p_pSprite);
	if (it != m_lSpriteList.end())
	{
		m_lSpriteList.erase(it);
	}
}

//------------------------------------------------------------------------------
// Method:    ClearSprites
// Returns:   void
// 
// Clears the list of sprites in the scene manager.
//------------------------------------------------------------------------------
void SceneManager::ClearSprites()
{
	m_lSpriteList.clear();
}


void SceneManager::AddPointLight(PointLight* p_pPointLight)
{
	m_lPointLightList.push_back(p_pPointLight);
}

void SceneManager::RemovePointLight(PointLight* p_pPointLight)
{
	PointLightList::iterator it = std::find(m_lPointLightList.begin(), m_lPointLightList.end(), p_pPointLight);
	if (it != m_lPointLightList.end())
	{
		m_lPointLightList.erase(it);
	}	
}

void SceneManager::ClearPointLights()
{
	m_lPointLightList.clear();
}
//------------------------------------------------------------------------------
// Method:    AttachCamera
// Parameter: SceneCamera * p_pCamera
// Returns:   void
// 
// Attaches the given camera to the scene
//------------------------------------------------------------------------------
void SceneManager::AttachCamera(SceneCamera* p_pCamera)
{
	m_pCamera = p_pCamera;
}

//------------------------------------------------------------------------------
// Method:    GetCamera
// Returns:   SceneCamera*
// 
// Returns the active camera.
//------------------------------------------------------------------------------
SceneCamera* SceneManager::GetCamera()
{
	return m_pCamera;
}

//------------------------------------------------------------------------------
// Method:    Render
// Returns:   void
// 
// Iterates the list of models, applies the camera params to the shader and 
// renders the model.
//------------------------------------------------------------------------------
void SceneManager::Render()
{
	// Can't render without a camera
	if (m_pCamera == NULL)
	{
		return;
	}

	// Get the view/proj matrices from the camera
	const glm::mat4& mProj = m_pCamera->GetProjectionMatrix();
	const glm::mat4& mView = m_pCamera->GetViewMatrix();

	// Iterate over the list of models and render them
	ModelList::iterator it = m_lModelList.begin(), end = m_lModelList.end();
	for (; it != end; ++it)
	{
		wolf::Model* pModel = static_cast<wolf::Model*>(*it);

		pModel->GetMaterial()->SetUniform("LightAmbient", wolf::Color4(0.6f,0.6f,0.4f,1.0f));

		//pModel->GetMaterial()->SetUniform("worldIT", glm::transpose(glm::inverse(pModel->GetTransform())));

		/*
		if (m_lPointLightList.size() > 0)
		{
			pModel->GetMaterial()->SetUniform("LightPos1", m_lPointLightList.at(0)->m_vPosition);
			pModel->GetMaterial()->SetUniform("LightAttenuation1", m_lPointLightList.at(0)->m_vAttenuation);
			pModel->GetMaterial()->SetUniform("LightDiffuse1", m_lPointLightList.at(0)->m_diffuse);
			pModel->GetMaterial()->SetUniform("LightSpecular1", m_lPointLightList.at(0)->m_specular);
			pModel->GetMaterial()->SetUniform("LightRange1", m_lPointLightList.at(0)->m_fRange);
		}

		if (m_lPointLightList.size() > 1)
		{
			pModel->GetMaterial()->SetUniform("LightPos2", m_lPointLightList.at(1)->m_vPosition);
			pModel->GetMaterial()->SetUniform("LightAttenuation2", m_lPointLightList.at(1)->m_vAttenuation);
			pModel->GetMaterial()->SetUniform("LightDiffuse2", m_lPointLightList.at(1)->m_diffuse);
			pModel->GetMaterial()->SetUniform("LightSpecular2", m_lPointLightList.at(1)->m_specular);
			pModel->GetMaterial()->SetUniform("LightRange2", m_lPointLightList.at(1)->m_fRange);
		}
		*/

		pModel->Render(mView, mProj);
	}


	SquareTextureList::iterator it1 = m_lSquareList.begin(), end1 = m_lSquareList.end();
	for (; it1 != end1; ++it1)
	{
		Square* pSquare = static_cast<Square*>(*it1);

		pSquare->GetMaterial()->SetUniform("LightAmbient", wolf::Color4(0.2f,0.2f,0.2f,1.0f));

		if (m_lPointLightList.size() > 0)
		{
			pSquare->GetMaterial()->SetUniform("LightPos1", m_lPointLightList.at(0)->m_vPosition);
			pSquare->GetMaterial()->SetUniform("LightAttenuation1", m_lPointLightList.at(0)->m_vAttenuation);
			pSquare->GetMaterial()->SetUniform("LightDiffuse1", m_lPointLightList.at(0)->m_diffuse);
			pSquare->GetMaterial()->SetUniform("LightSpecular1", m_lPointLightList.at(0)->m_specular);
			pSquare->GetMaterial()->SetUniform("LightRange1", m_lPointLightList.at(0)->m_fRange);
		}

		if (m_lPointLightList.size() > 1)
		{
			pSquare->GetMaterial()->SetUniform("LightPos2", m_lPointLightList.at(1)->m_vPosition);
			pSquare->GetMaterial()->SetUniform("LightAttenuation2", m_lPointLightList.at(1)->m_vAttenuation);
			pSquare->GetMaterial()->SetUniform("LightDiffuse2", m_lPointLightList.at(1)->m_diffuse);
			pSquare->GetMaterial()->SetUniform("LightSpecular2", m_lPointLightList.at(1)->m_specular);
			pSquare->GetMaterial()->SetUniform("LightRange2", m_lPointLightList.at(1)->m_fRange);
		}

		pSquare->Render(mView, mProj);
	}

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// Render the sprite list with an ortho camera. 
	// TODO: We should really add the camera separately rather than hard code it.
	const glm::mat4 mOrthoProj = glm::ortho(0.0f,1280.0f,720.0f,0.0f,0.0f,1000.0f);
	SpriteList::iterator sIt = m_lSpriteList.begin(), sEnd = m_lSpriteList.end();
	for (; sIt != sEnd; ++sIt)
	{
		wolf::Sprite* pSprite = static_cast<wolf::Sprite*>(*sIt);
		pSprite->Render(mOrthoProj);
	}

	//render HUD textbox
	m_pTextBox->Render();
}

void SceneManager::Update(float p_fDelta)
{
	ModelList::iterator it = m_lModelList.begin(), end = m_lModelList.end();
	for (; it != end; ++it)
	{
		wolf::Model* pModel = static_cast<wolf::Model*>(*it);
		pModel->Update(p_fDelta);
	}

}