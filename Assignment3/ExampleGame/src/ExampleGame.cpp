//------------------------------------------------------------------------
// ExampleGame
//
// Created:	2012/12/06
// Author:	Carel Boers
//	
// Main game class. Derives from Common::Game.
//------------------------------------------------------------------------

#include "ComponentAnimController.h"
#include "ComponentCharacterController.h"
#include "ComponentRenderableMesh.h"
#include "ExampleGame.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "W_Model.h"
#include "Assignment2/ExampleGame/ComponentRenderableSquare.h"
#include "Assignment2/ExampleGame/ComponentCamera.h"
#include "Assignment2/ExampleGame/ComponentCameraFollow.h"
#include "Assignment2/ExampleGame/ComponentCoinScore.h"
#include "Assignment2/ExampleGame/ComponentCoinLife.h"
#include "Assignment2/ExampleGame/ComponentCoinMovement.h"
#include "Assignment2/ExampleGame/ComponentCollision.h"
#include "Assignment2/ExampleGame/EventManager.h"
#include "Assignment2/ExampleGame/ComponentTimerLogic.h"
#include "Assignment2/ExampleGame/Textbox/TTextBox.h"
#include "Assignment2/ExampleGame/Textbox/TFont.h"
#include "Assignment2/ExampleGame/ComponentCameraFollow.h"
#include "Assignment2/ExampleGame/ComponentCamera.h"

using namespace week2;

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
	m_pGameObjectManager(NULL)
{
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

	// Initialize our GameObjectManager
	m_pGameObjectManager = new Common::GameObjectManager();

	EventManager::CreateInstance();

	m_pGameObjectManager->RegisterComponentFactory("GOC_RenderableMesh", ComponentRenderableMesh::CreateComponent);
	m_pGameObjectManager->RegisterComponentFactory("GOC_AnimController", ComponentAnimController::CreateComponent);
	m_pGameObjectManager->RegisterComponentFactory("GOC_CharacterController", ComponentCharacterController::CreateComponent);
	m_pGameObjectManager->RegisterComponentFactory("GOC_RenderableSquare", ComponentRenderableSquare::CreateComponent);
	m_pGameObjectManager->RegisterComponentFactory("GOC_CoinScore", ComponentCoinScore::CreateComponent);
	m_pGameObjectManager->RegisterComponentFactory("GOC_LifeSpan", ComponentCoinLife::CreateComponent);
	m_pGameObjectManager->RegisterComponentFactory("GOC_CollisionSphere", ComponentCollision::CreateComponent);
	m_pGameObjectManager->RegisterComponentFactory("GOC_CoinMovement", ComponentCoinMovement::CreateComponent);
	m_pGameObjectManager->RegisterComponentFactory("GOC_TimerLogic", ComponentTimerLogic::CreateComponent);
	m_pGameObjectManager->RegisterComponentFactory("GOC_CameraFollow", ComponentCameraFollow::CreateComponent);
	m_pGameObjectManager->RegisterComponentFactory("GOC_Camera", ComponentCamera::CreateComponent);

	// Create a Character GameObject
	Common::GameObject* pCharacter = m_pGameObjectManager->CreateGameObject("Assignment2/ExampleGame/data/xml/character.xml");
	m_pGameObjectManager->SetGameObjectGUID(pCharacter, "character");
	pCharacter->GetTransform().Scale(glm::vec3(0.05f, 0.05, 0.05f));
	pCharacter->GetTransform().SetTranslation(glm::vec3(3.0f, 0.0, 0.0f));
	pCharacter->GetTransform().Rotate(glm::vec3(0.0f,40.0f,0.0f));

	
	// lamp post
	Common::GameObject* pLamp = m_pGameObjectManager->CreateGameObject("Assignment2/ExampleGame/data/xml/lamp.xml");
    m_pGameObjectManager->SetGameObjectGUID(pLamp, "lamp");
	pLamp->GetTransform().Scale(glm::vec3(0.4f, 0.4, 0.4f));


	// Create ground
	Common::GameObject* pGround = m_pGameObjectManager->CreateGameObject("Assignment2/ExampleGame/data/xml/ground.xml");

	// Create timer
	Common::GameObject* pTimer = m_pGameObjectManager->CreateGameObject("Assignment2/ExampleGame/data/xml/timer.xml");
	m_pGameObjectManager->SetGameObjectGUID(pTimer, "timer");

	// HUD
	TFont tfont = TFont("Assignment2/ExampleGame/data/font/bm_0.tga","Assignment2/ExampleGame/data/font/bm.fnt");
	string txt = std::string("Score: 0");
	TTextBox* textbox1 = new TTextBox(&tfont,txt,	160, 40);
	textbox1->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	textbox1->SetPos(50,50);
	textbox1->Init();
	Common::SceneManager::Instance()->AttachHUDTextBox(textbox1);
	
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
	EventManager::Instance()->Update(p_fDelta);
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
}