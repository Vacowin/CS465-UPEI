//------------------------------------------------------------------------
// ExampleGame
//
// Created:	2012/12/06
// Author:	Carel Boers
//	
// Main game class. Derives from Common::Game.
//------------------------------------------------------------------------

#include "ExampleGame.h"
#include "W_Model.h"

using namespace week1;


struct DirectionalLight
{
	glm::vec3		m_vDirection;
	wolf::Color4    m_ambient;
	wolf::Color4	m_diffuse;
	wolf::Color4	m_specular;
	DirectionalLight() : m_diffuse(0,0,0,0), m_specular(0,0,0,0), m_ambient(0,0,0,0) {}    
};

static DirectionalLight g_light1;

//------------------------------------------------------------------------------
// Method:    ExampleGame
// Parameter: void
// Returns:   
// 
// Constructor
//------------------------------------------------------------------------------
ExampleGame::ExampleGame()
	:
	m_pModel(NULL)
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
	assert(!m_pModel);
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
	// Initialize the light parameters
	g_light1.m_diffuse = wolf::Color4(1.0f,1.0f,1.0f,1.0f);
	g_light1.m_ambient = wolf::Color4(0.1f,0.1f,0.1f,1.0f);
	g_light1.m_specular = wolf::Color4(1.0f,1.0f,1.0f,1.0f);
	g_light1.m_vDirection = glm::vec3(0.0f,0.0f,-1.0f);

	// Initialize the model
	m_pModel = new wolf::Model("week1/ExampleGame/data/zombie/zombie.pod", "week1/ExampleGame/data/zombie/", "week1/ExampleGame/data/skinned.vsh", "week1/ExampleGame/data/skinned.fsh");
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
void ExampleGame::Render()
{
	// Set the light parameters
	m_pModel->GetMaterial()->SetUniform("ViewDir", glm::vec3(0.0f,0.0f,1.0f));
	m_pModel->GetMaterial()->SetUniform("LightAmbient", g_light1.m_ambient);
	m_pModel->GetMaterial()->SetUniform("LightDiffuse", g_light1.m_diffuse);
	m_pModel->GetMaterial()->SetUniform("LightSpecular", g_light1.m_specular);
	m_pModel->GetMaterial()->SetUniform("LightDir", g_light1.m_vDirection);

	// Set the world/view/proj matrices
	glm::mat4 mProj = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
	glm::mat4 mView = glm::lookAt(glm::vec3(0.0f, 90.0f, 300.0f), glm::vec3(0.0f, 90.0f, 300.0f) - glm::vec3(0.0f,0.0f,1.0f), glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 mWorld = glm::rotate(0.0f, 0.0f, 1.0f, 0.0f);

	// Render the model
	m_pModel->SetTransform(mWorld);
	m_pModel->Render(mView,mProj);
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
	if (m_pModel)
	{
		delete m_pModel;
		m_pModel = NULL;
	}
}