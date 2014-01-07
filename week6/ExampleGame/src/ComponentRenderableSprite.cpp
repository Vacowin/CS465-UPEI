//------------------------------------------------------------------------
// ComponentRenderableSprite
//
// Created:	2012/12/14
// Author:	Carel Boers
//	
// This class implements a renderable component that is a sprite.
//------------------------------------------------------------------------

#include "W_Model.h"
#include "ComponentRenderableSprite.h"
#include "GameObject.h"
#include "SceneManager.h"

using namespace week6;

//------------------------------------------------------------------------------
// Method:    ComponentRenderableSprite
// Returns:   
// 
// Constructor.
//------------------------------------------------------------------------------
ComponentRenderableSprite::ComponentRenderableSprite()
	:
	m_pSprite(NULL)
{
}

//------------------------------------------------------------------------------
// Method:    ~ComponentRenderableSprite
// Returns:   
// 
// Destructor.
//------------------------------------------------------------------------------
ComponentRenderableSprite::~ComponentRenderableSprite()
{
	// Remove the sprite from the scene
	Common::SceneManager::Instance()->RemoveSprite(m_pSprite);

	// Delete the sprite
	if (m_pSprite)
	{
		delete m_pSprite;
		m_pSprite = NULL;
	}
}

//------------------------------------------------------------------------------
// Method:    Init
// Parameter: const std::string & p_strTexturePath
// Parameter: const std::string & p_strVertexProgramPath
// Parameter: const std::string & p_strFragmentProgramPath
// Parameter: const glm::vec2& p_vDimensions
// Returns:   void
// 
// Initializes this component by loading the renderable object.
//------------------------------------------------------------------------------
void ComponentRenderableSprite::Init(const std::string &p_strTexturePath, const std::string &p_strVertexProgramPath, const std::string &p_strFragmentProgramPath, const glm::vec2& p_vDimensions)
{
	m_pSprite = new wolf::Sprite(p_strTexturePath, p_strVertexProgramPath, p_strFragmentProgramPath, p_vDimensions);
	Common::SceneManager::Instance()->AddSprite(m_pSprite);
}

//------------------------------------------------------------------------------
// Method:    SyncTransform
// Returns:   void
// 
// Syncs the sprite transform with the game object transform.
//------------------------------------------------------------------------------
void ComponentRenderableSprite::SyncTransform()
{
	m_pSprite->SetTransform(this->GetGameObject()->GetTransform().GetTransformation());
}

//------------------------------------------------------------------------------
// Method:    ExportToLua
// Returns:   void
// 
// Export interface to Lua.
//------------------------------------------------------------------------------
void ComponentRenderableSprite::ExportToLua()
{
	LuaPlus::LuaObject metaTable = Common::LuaScriptManager::Instance()->GetLuaState()->GetGlobals().CreateTable("ComponentRenderableSpriteMetaTable");
	metaTable.SetObject("__index", metaTable);

	// Register methods
	Common::LuaScriptManager::Instance()->GetLuaState()->GetGlobals().RegisterDirect("CreateComponentRenderableSprite", &ComponentRenderableSprite::LuaNew);
	metaTable.RegisterObjectDirect("Init", (ComponentRenderableSprite*) 0, &ComponentRenderableSprite::LuaInit);
}

//------------------------------------------------------------------------------
// Method:    LuaNew
// Returns:   LuaPlus::LuaObject
// 
// Construction of ComponentRenderableSprite to be exported to Lua.
//------------------------------------------------------------------------------
LuaPlus::LuaObject ComponentRenderableSprite::LuaNew()
{
	ComponentRenderableSprite* pComponent = new ComponentRenderableSprite();
	LuaPlus::LuaObject luaInstance;
	luaInstance.AssignNewTable(Common::LuaScriptManager::Instance()->GetLuaState());

	luaInstance.SetLightUserData("__object", pComponent);

	LuaPlus::LuaObject metaTable = Common::LuaScriptManager::Instance()->GetLuaState()->GetGlobals().GetByName("ComponentRenderableSpriteMetaTable");
	luaInstance.SetMetaTable(metaTable);

	return luaInstance;
}

//------------------------------------------------------------------------------
// Method:    LuaInit
// Parameter: const char * p_strTexturePath
// Parameter: const char * p_strVertexProgramPath
// Parameter: const char * p_strFragmentProgramPath
// Parameter: float p_fSizeX
// Parameter: float p_fXizeY
// Returns:   void
// 
// Initializes this component by loading the renderable object.
//------------------------------------------------------------------------------
void ComponentRenderableSprite::LuaInit(const char* p_strTexturePath, const char* p_strVertexProgramPath, const char* p_strFragmentProgramPath, float p_fSizeX, float p_fXizeY)
{
	this->Init(std::string(p_strTexturePath), std::string(p_strVertexProgramPath), std::string(p_strFragmentProgramPath), glm::vec2(p_fSizeX, p_fXizeY));
}