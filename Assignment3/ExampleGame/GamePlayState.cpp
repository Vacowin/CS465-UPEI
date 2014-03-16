#include "GamePlayState.h"
#include "Assignment3/ExampleGame/src/ComponentAnimController.h"
#include "Assignment3/ExampleGame/src/ComponentCharacterController.h"
#include "Assignment3/ExampleGame/src/ComponentRenderableMesh.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "W_Model.h"
#include "Assignment3/ExampleGame/ComponentRenderableSquare.h"
#include "Assignment3/ExampleGame/ComponentCamera.h"
#include "Assignment3/ExampleGame/ComponentCameraFollow.h"
#include "Assignment3/ExampleGame/ComponentCoinScore.h"
#include "Assignment3/ExampleGame/ComponentCoinLife.h"
#include "Assignment3/ExampleGame/ComponentCoinMovement.h"
#include "Assignment3/ExampleGame/ComponentCollision.h"
#include "Assignment3/ExampleGame/EventManager.h"
#include "Assignment3/ExampleGame/ComponentTimerLogic.h"
#include "Assignment3/ExampleGame/Textbox/TTextBox.h"
#include "Assignment3/ExampleGame/Textbox/TFont.h"
#include "Assignment3/ExampleGame/ComponentCameraFollow.h"
#include "Assignment3/ExampleGame/ComponentCamera.h"
#include "common/BulletPhysicsManager.h"
#include "Assignment3/ExampleGame/ComponentRigidBody.h"

using namespace week2;

GamePlayState::GamePlayState()
{
}


GamePlayState::~GamePlayState()
{
}

void GamePlayState::Enter()
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
	m_pGameObjectManager->RegisterComponentFactory("GOC_RigidBody", ComponentRigidBody::CreateComponent);

	// Create a Physics Manager to manage physics simulation
	Common::BulletPhysicsManager::CreateInstance("Assignment3/ExampleGame/data/physics_materials.xml",
												"Assignment3/ExampleGame/data/shaders/lines.vsh", 
												"Assignment3/ExampleGame/data/shaders/lines.fsh");

	// Create a Character GameObject
	Common::GameObject* pCharacter = m_pGameObjectManager->CreateGameObject("Assignment3/ExampleGame/data/xml/character.xml");
	m_pGameObjectManager->SetGameObjectGUID(pCharacter, "character");
	pCharacter->GetTransform().Scale(glm::vec3(0.05f, 0.05, 0.05f));
	pCharacter->GetTransform().SetTranslation(glm::vec3(5.0f, 0.0, 0.0f));
	pCharacter->GetTransform().Rotate(glm::vec3(0.0f,80.0f,0.0f));
	ComponentRigidBody* pCharRigid = static_cast<ComponentRigidBody*>(pCharacter->GetComponent("GOC_RigidBody"));
	pCharRigid->BindGameObject();

	// lamp post
	Common::GameObject* pLamp = m_pGameObjectManager->CreateGameObject("Assignment3/ExampleGame/data/xml/lamp.xml");
    m_pGameObjectManager->SetGameObjectGUID(pLamp, "lamp");
	pLamp->GetTransform().Scale(glm::vec3(0.4f, 0.4, 0.4f));
	ComponentRigidBody* pLampRigid = static_cast<ComponentRigidBody*>(pLamp->GetComponent("GOC_RigidBody"));
	pLampRigid->BindGameObject();

	// Create ground
	Common::GameObject* pGround = m_pGameObjectManager->CreateGameObject("Assignment3/ExampleGame/data/xml/ground.xml");
	ComponentRigidBody* pGroundRigid = static_cast<ComponentRigidBody*>(pGround->GetComponent("GOC_RigidBody"));
	pGroundRigid->BindGameObject();

	// Create walls
	Common::GameObject* pWall1 = m_pGameObjectManager->CreateGameObject("Assignment3/ExampleGame/data/xml/wall.xml");
	m_pGameObjectManager->SetGameObjectGUID(pWall1, "wall1");
	pWall1->GetTransform().Rotate(glm::vec3(90.0f,0.0f,0.0f));
	pWall1->GetTransform().Translate(glm::vec3(0.0f,150.0f,75.0f));
	ComponentRigidBody* pWall1Rigid = static_cast<ComponentRigidBody*>(pWall1->GetComponent("GOC_RigidBody"));
	pWall1Rigid->BindGameObject();

	Common::GameObject* pWall2 = m_pGameObjectManager->CreateGameObject("Assignment3/ExampleGame/data/xml/wall.xml");
	m_pGameObjectManager->SetGameObjectGUID(pWall2, "wall2");
	pWall2->GetTransform().Rotate(glm::vec3(90.0f,0.0f,0.0f));
	pWall2->GetTransform().Translate(glm::vec3(0.0f,150.0f,-75.0f));
	ComponentRigidBody* pWall2Rigid = static_cast<ComponentRigidBody*>(pWall2->GetComponent("GOC_RigidBody"));
	pWall2Rigid->BindGameObject();

	Common::GameObject* pWall3 = m_pGameObjectManager->CreateGameObject("Assignment3/ExampleGame/data/xml/wall.xml");
	m_pGameObjectManager->SetGameObjectGUID(pWall3, "wall3");
	pWall3->GetTransform().Rotate(glm::vec3(90.0f,90.0f,0.0f));
	pWall3->GetTransform().Translate(glm::vec3(75.0f,150.0f,0.0f));
	ComponentRigidBody* pWall3Rigid = static_cast<ComponentRigidBody*>(pWall3->GetComponent("GOC_RigidBody"));
	pWall3Rigid->BindGameObject();

	Common::GameObject* pWall4 = m_pGameObjectManager->CreateGameObject("Assignment3/ExampleGame/data/xml/wall.xml");
	m_pGameObjectManager->SetGameObjectGUID(pWall4, "wall4");
	pWall4->GetTransform().Rotate(glm::vec3(90.0f,90.0f,0.0f));
	pWall4->GetTransform().Translate(glm::vec3(-75.0f,150.0f,0.0f));
	ComponentRigidBody* pWall4Rigid = static_cast<ComponentRigidBody*>(pWall4->GetComponent("GOC_RigidBody"));
	pWall4Rigid->BindGameObject();

	// Create timer
	Common::GameObject* pTimer = m_pGameObjectManager->CreateGameObject("Assignment3/ExampleGame/data/xml/timer.xml");
	m_pGameObjectManager->SetGameObjectGUID(pTimer, "timer");

	// HUD
	TFont tfont = TFont("Assignment3/ExampleGame/data/font/bm_0.tga","Assignment3/ExampleGame/data/font/bm.fnt");
	string txt = std::string("Score: 0");
	TTextBox* textbox1 = new TTextBox(&tfont,txt,	160, 40);
	textbox1->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	textbox1->SetPos(50,50);
	textbox1->Init();
	Common::SceneManager::Instance()->AttachHUDTextBox(textbox1);
	
	for (int j = 0;j<4;j++)
	{
		float randX = (rand() % 60) - (rand() % 10);
		float randZ = (rand() % 60) - (rand() % 10);
		for (int i = 0; i < 9; ++i)
		{
			Common::GameObject* pCrate = m_pGameObjectManager->CreateGameObject("Assignment3/ExampleGame/data/xml/crate.xml");
			char buff[64];
			sprintf(buff, "Crate%d",j*9+ i);
			m_pGameObjectManager->SetGameObjectGUID(pCrate, buff);

			glm::vec3 vPosition;
			vPosition.x = randX;
			vPosition.y = i*3.1f;
			vPosition.z = randZ;
			pCrate->GetTransform().SetTranslation(vPosition);

			ComponentRigidBody* pCrateRigid = static_cast<ComponentRigidBody*>(pCrate->GetComponent("GOC_RigidBody"));
			pCrateRigid->BindGameObject();
		}
	}
}

void GamePlayState::Update(float p_fDelta)
{
	Common::BulletPhysicsManager::Instance()->Update(p_fDelta);
	EventManager::Instance()->Update(p_fDelta);
	m_pGameObjectManager->Update(p_fDelta);
	m_pGameObjectManager->SyncTransforms();

	static bool bLastKeyDown = false;
	bool bCurrentKeyDown = glfwGetKey('Z');
	if (bCurrentKeyDown && !bLastKeyDown)
	{
		Common::BulletPhysicsManager::Instance()->ToggleDebugRendering();
	}
	bLastKeyDown = bCurrentKeyDown;
}

void GamePlayState::Suspend()
{
}

void GamePlayState::Resume()
{
}

void GamePlayState::Exit()
{
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