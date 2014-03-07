//------------------------------------------------------------------------
// ExampleGame
//
// Created:	2012/12/06
// Author:	Carel Boers
//	
// Main game class. Derives from Common::Game.
//------------------------------------------------------------------------


#include "ComponentAnimController.h"
#include "ExampleGame.h"
#include "GameObject.h"
#include "LuaScriptManager.h"
#include "SceneManager.h"
#include "StateGameplay.h"
#include "StateMainMenu.h"
#include "StateLeaderBoard.h"
#include "States.h"
#include "W_Model.h"
#include "windows.h"

using namespace week6;

ExampleGame* ExampleGame::s_pInstance = NULL;

//------------------------------------------------------------------------------
// Method:    ExampleGame
// Parameter: void
// Returns:   
// 
// Constructor
//------------------------------------------------------------------------------
ExampleGame::ExampleGame()
	: 
	m_pSceneCamera(NULL),
	m_pGameObjectManager(NULL),
	m_pStateMachine(NULL)
{
	s_pInstance = this;
}

//------------------------------------------------------------------------------
// Method:    ~ExampleGame
// Parameter: void
// Returns:   
// 
// Destructor.
//------------------------------------------------------------------------------
ExampleGame::~ExampleGame()
{
	assert(!m_pGameObjectManager);
	assert(!m_pSceneCamera);
	assert(!m_pStateMachine);
}

//------------------------------------------------------------------------------
// Method:    ExportToLua
// Returns:   void
// 
// Export interface to Lua.
//------------------------------------------------------------------------------
void ExampleGame::ExportToLua()
{
	LuaPlus::LuaObject metaTable = Common::LuaScriptManager::Instance()->GetLuaState()->GetGlobals().CreateTable("GameMetaTable");
	metaTable.SetObject("__index", metaTable);
	Common::LuaScriptManager::Instance()->GetLuaState()->GetGlobals().RegisterDirect("GetGame", &ExampleGame::GetGame);
	Common::LuaScriptManager::Instance()->GetLuaState()->GetGlobals().RegisterDirect("LuaPrint", &ExampleGame::LuaPrint);
	metaTable.RegisterObjectDirect("GetGameObjectManager", (ExampleGame*)0, &ExampleGame::GetGameObjectManager);
}

//------------------------------------------------------------------------------
// Method:    GetGame
// Returns:   LuaPlus::LuaObject
// 
// Returns an instance of the Game.
//------------------------------------------------------------------------------
LuaPlus::LuaObject ExampleGame::GetGame()
{
	LuaPlus::LuaObject luaInstance;
	luaInstance.AssignNewTable(Common::LuaScriptManager::Instance()->GetLuaState());

	luaInstance.SetLightUserData("__object", s_pInstance);

	LuaPlus::LuaObject metaTable = Common::LuaScriptManager::Instance()->GetLuaState()->GetGlobals().GetByName("GameMetaTable");
	luaInstance.SetMetaTable(metaTable);

	return luaInstance;
}

//------------------------------------------------------------------------------
// Method:    LuaPrint
// Parameter: const char * p_strDebugString
// Returns:   void
// 
// Prints a debug string to the console.
//------------------------------------------------------------------------------
void ExampleGame::LuaPrint(const char* p_strDebugString)
{
	static char buffer[1024];
	sprintf_s(buffer, "LUA PRINT[%s]\n", p_strDebugString);
	OutputDebugString(buffer);
}

//------------------------------------------------------------------------------
// Method:    GetGameObjectManager
// Returns:   LuaPlus::LuaObject
// 
// Returns the GameObjectManager as a LuaObject instance for use in Lua.
//------------------------------------------------------------------------------
LuaPlus::LuaObject ExampleGame::GetGameObjectManager()
{
	LuaPlus::LuaObject luaInstance;
	luaInstance.AssignNewTable(Common::LuaScriptManager::Instance()->GetLuaState());

	luaInstance.SetLightUserData("__object", m_pGameObjectManager);

	LuaPlus::LuaObject metaTable = Common::LuaScriptManager::Instance()->GetLuaState()->GetGlobals().GetByName("GameObjectManagerMetaTable");
	luaInstance.SetMetaTable(metaTable);

	return luaInstance;
}

//------------------------------------------------------------------------------
// Method:    Init
// Returns:   bool
// 
// Overridden from Common::Game::Init(). Called when it's time to initialize our
// game. Returns true on successful initialization, false otherwise. If false is
// returned, the game will shut down.
//------------------------------------------------------------------------------
bool ExampleGame::Init()
{
	// Initialize our Scene Manager
	Common::SceneManager::CreateInstance();

	// Initialize our Scene Camera and attach it to the Scene Manager
	m_pSceneCamera = new Common::SceneCamera(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f, glm::vec3(0.0f, 5.0f, 15.0f), glm::vec3(0.0f,5.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
	Common::SceneManager::Instance()->AttachCamera(m_pSceneCamera);
	
	// Initialize Lua Script Manager
	Common::LuaScriptManager::CreateInstance();

	// Initialize our GameObjectManager
	m_pGameObjectManager = new Common::GameObjectManager();

	// Register factory methods
	m_pGameObjectManager->RegisterComponentFactory("GOC_AnimController", ComponentAnimController::CreateComponent);

	// Initialize the StateMachine and supported states and go to the main state
	m_pStateMachine = new Common::StateMachine();
	m_pStateMachine->RegisterState(eStateGameplay_MainMenu, new StateMainMenu());
	m_pStateMachine->RegisterState(eStateGameplay_Gameplay, new StateGameplay());
	m_pStateMachine->RegisterState(eStateGameplay_LeaderBoard, new StateLeaderBoard());
	m_pStateMachine->GoToState(eStateGameplay_MainMenu);

	// Everything initialized OK.
	return true;
}

//------------------------------------------------------------------------------
// Method:    Update
// Parameter: float p_fDelta
// Returns:   bool
// 
// Overridden from Common::Game::Update(). Called once per frame during the main
// loop of the game. The game state is updated here. Returns true on success, 
// false otherwise. If false is returned, the game will shutdown.
//------------------------------------------------------------------------------
bool ExampleGame::Update(float p_fDelta)
{
	m_pStateMachine->Update(p_fDelta);
	m_pGameObjectManager->Update(p_fDelta);
	return true;
}

//------------------------------------------------------------------------------
// Method:    Render
// Returns:   void
// 
// Overridden from Common::Game::Render(). Called once per frame during the main
// loop of the game. Any objects in the game that need to be drawn are rendered
// here.
//------------------------------------------------------------------------------
void ExampleGame::Render()
{
	// Sync transforms to render components
	m_pGameObjectManager->SyncTransforms();

	// Render the scene
	Common::SceneManager::Instance()->Render();
}

//------------------------------------------------------------------------------
// Method:    Shutdown
// Returns:   void
// 
// Called when the game is shutting down. All dynamic memory needs to be cleaned
// up.
//------------------------------------------------------------------------------
void ExampleGame::Shutdown()
{
	// Destroy our states and state machine
	delete m_pStateMachine;

	// Clear our Game Objects
	m_pGameObjectManager->DestroyAllGameObjects();
	delete m_pGameObjectManager;
	m_pGameObjectManager = NULL;

	// Delete our camera
	if (m_pSceneCamera)
	{
		delete m_pSceneCamera;
		m_pSceneCamera = NULL;
	}

	// Destroy the Scene Manager
	Common::SceneManager::DestroyInstance();

	// Destroy the Lua script manager
	Common::LuaScriptManager::DestroyInstance();
}