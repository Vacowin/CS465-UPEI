//------------------------------------------------------------------------
// ExampleGame2
//
// Created:	2012/12/06
// Author:	Carel Boers
//	
// Main game class. Derives from Common::Game.
//------------------------------------------------------------------------

#include "ExampleGame2.h"
#include "W_Model.h"

using namespace week1;

//------------------------------------------------------------------------------
// Method:    ExampleGame2
// Parameter: void
// Returns:   
// 
// Constructor
//------------------------------------------------------------------------------
ExampleGame2::ExampleGame2()
	:
	m_pSceneCamera(NULL),
	m_pModel(NULL)
{
}

//------------------------------------------------------------------------------
// Method:    ~ExampleGame2
// Parameter: void
// Returns:   
// 
// Destructor.
//------------------------------------------------------------------------------
ExampleGame2::~ExampleGame2()
{
	assert(!m_pModel);
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
bool ExampleGame2::Init()
{ 
	// Initialize our Scene Manager
	Common::SceneManager::CreateInstance();

	// Initialize our Scene Camera and attach it to the Scene Manager
	m_pSceneCamera = new Common::SceneCamera(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f, glm::vec3(0.0f, 90.0f, 300.0f), glm::vec3(0.0f,90.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
	Common::SceneManager::Instance()->AttachCamera(m_pSceneCamera);

	// Initialize the model and add it the Scene Manager
	m_pModel = new wolf::Model("week1/ExampleGame2/data/zombie/zombie.pod", "week1/ExampleGame2/data/zombie/", "week1/ExampleGame2/data/skinned.vsh", "week1/ExampleGame2/data/skinned.fsh");
	Common::SceneManager::Instance()->AddModel(m_pModel);

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
bool ExampleGame2::Update(float p_fDelta)
{
	m_pModel->Update(p_fDelta);
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
void ExampleGame2::Render()
{
	Common::SceneManager::Instance()->Render();
}

//------------------------------------------------------------------------------
// Method:    Shutdown
// Returns:   void
// 
// Called when the game is shutting down. All dynamic memory needs to be cleaned
// up.
//------------------------------------------------------------------------------
void ExampleGame2::Shutdown()
{
	if (m_pModel)
	{
		Common::SceneManager::Instance()->RemoveModel(m_pModel);
		delete m_pModel;
		m_pModel = NULL;
	}

	if (m_pSceneCamera)
	{
		delete m_pSceneCamera;
		m_pSceneCamera = NULL;
	}

	Common::SceneManager::DestroyInstance();
}