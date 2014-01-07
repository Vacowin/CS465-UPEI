//------------------------------------------------------------------------
// ComponentAnimController
//
// Created:	2012/12/14
// Author:	Carel Boers
//	
// This class implements an animation controller. It manages a list of 
// animations and applies them to a ComponentRenderable on the parent
// GameObject (if one exists).
//------------------------------------------------------------------------

#include "W_Model.h"
#include "ComponentAnimController.h"
#include "ComponentRenderableMesh.h"
#include "GameObject.h"

using namespace week2;

//------------------------------------------------------------------------------
// Method:    ComponentAnimController
// Parameter: int p_iAnimSpeed - animation speed (FPS)
// Returns:   
// 
// Constructor.
//------------------------------------------------------------------------------
ComponentAnimController::ComponentAnimController(int p_iAnimSpeed)
	:
	m_iAnimSpeed(p_iAnimSpeed),
	m_pCurrentAnim(NULL),
	m_fAnimFrame(0.0f)
{
}

//------------------------------------------------------------------------------
// Method:    ~ComponentAnimController
// Returns:   
// 
// Destructor.
//------------------------------------------------------------------------------
ComponentAnimController::~ComponentAnimController()
{
	AnimMap::iterator it = m_animMap.begin(), end = m_animMap.end();
	for (; it != end; ++it)
	{
		m_pCurrentAnim = static_cast<Anim*>(it->second);
		delete m_pCurrentAnim;
	}
	m_animMap.clear();
}

//------------------------------------------------------------------------------
// Method:    Update
// Parameter: float p_fDelta
// Returns:   void
// 
// Updates the current animation and looks for a sibling component in the parent
// GameObject in order to set the animation frame.
//------------------------------------------------------------------------------
void ComponentAnimController::Update(float p_fDelta)
{
	if (m_pCurrentAnim)
	{
		m_fAnimFrame += (p_fDelta * static_cast<float>(m_iAnimSpeed));
		if(m_fAnimFrame >= static_cast<float>(m_pCurrentAnim->m_iEndFrame))
		{
			if (m_pCurrentAnim->m_bLoop)
			{
				m_fAnimFrame = static_cast<float>(m_pCurrentAnim->m_iStartFrame);
			}
			else
			{
				m_fAnimFrame = 0.0f;
				m_pCurrentAnim = NULL;
			}
		}

		// If the animation is still playing, then set the frame on our sibling component
		if (m_pCurrentAnim)
		{
			// Get the parent GameObject and find it's Renderable component
			Common::GameObject* pGameObject = this->GetGameObject();
			ComponentBase* pComponent = pGameObject->GetComponent("GOC_Renderable");
			if (pComponent)
			{
				ComponentRenderableMesh* pRenderableComponent = static_cast<ComponentRenderableMesh*>(pComponent);
				pRenderableComponent->GetModel()->SetAnimFrame(m_fAnimFrame);
			}
		}
	}
}

//------------------------------------------------------------------------------
// Method:    AddAnim
// Parameter: const std::string & p_strAnimName
// Parameter: int p_iStartFrame
// Parameter: int p_iEndFrame
// Parameter: bool p_bLoop
// Returns:   void
// 
// Adds an animation to the animation controller.
//------------------------------------------------------------------------------
void ComponentAnimController::AddAnim(const std::string &p_strAnimName, int p_iStartFrame, int p_iEndFrame, bool p_bLoop)
{
	// Make sure we don't already have an anim with this name
	if (m_animMap.find(p_strAnimName) == m_animMap.end())
	{
		Anim* pAnim = new Anim(p_strAnimName, p_iStartFrame, p_iEndFrame, p_bLoop);
		m_animMap.insert(std::make_pair<std::string, Anim*>(p_strAnimName, pAnim));
	}
}

//------------------------------------------------------------------------------
// Method:    SetAnim
// Parameter: const std::string & p_strAnimName
// Returns:   void
// 
// Sets the given animation as the current animation.
//------------------------------------------------------------------------------
void ComponentAnimController::SetAnim(const std::string &p_strAnimName)
{
	AnimMap::const_iterator it = m_animMap.find(p_strAnimName);
	if (it != m_animMap.end())
	{
		m_pCurrentAnim = static_cast<Anim*>(it->second);
		m_fAnimFrame = m_pCurrentAnim->m_iStartFrame;
	}
}
