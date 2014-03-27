#include "GamePlayState.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "W_Model.h"

#include "Assignment4/ExampleGame/Textbox/TTextBox.h"
#include "Assignment4/ExampleGame/Textbox/TFont.h"
#include "common/BulletPhysicsManager.h"
#include "Assignment4/ExampleGame/ComponentRigidBody.h"
#include "Assignment4/ExampleGame/States.h"
#include "Assignment4/ExampleGame/src/ExampleGame.h"
#include "Assignment4/ExampleGame/ComponentMouseClick.h"
#include "Assignment4/ExampleGame/src/ComponentCharacterController.h"
#include "Assignment4/ExampleGame/ComponentCoinMovement.h"
#include "Assignment4/ExampleGame/ComponentTimerLogic.h"

using namespace week2;

GamePlayState::GamePlayState()
{
}


GamePlayState::~GamePlayState()
{
}

void GamePlayState::Enter()
{
	m_pGameObjectManager = ExampleGame::GetInstance()->GameObjectManager();
	// Create a Physics Manager to manage physics simulation
	Common::BulletPhysicsManager::CreateInstance("Assignment4/ExampleGame/data/physics_materials.xml",
												"Assignment4/ExampleGame/data/shaders/lines.vsh", 
												"Assignment4/ExampleGame/data/shaders/lines.fsh");

	// Create a Character GameObject
	Common::GameObject* pCharacter = m_pGameObjectManager->CreateGameObject("Assignment4/ExampleGame/data/xml/character.xml");
	m_pGameObjectManager->SetGameObjectGUID(pCharacter, "character");
	pCharacter->GetTransform().Scale(glm::vec3(0.05f, 0.05, 0.05f));
	pCharacter->GetTransform().SetTranslation(glm::vec3(5.0f, 0.0, 0.0f));
	pCharacter->GetTransform().Rotate(glm::vec3(0.0f,80.0f,0.0f));
	ComponentRigidBody* pCharRigid = static_cast<ComponentRigidBody*>(pCharacter->GetComponent("GOC_RigidBody"));
	pCharRigid->BindGameObject();

	// lamp post
	Common::GameObject* pLamp = m_pGameObjectManager->CreateGameObject("Assignment4/ExampleGame/data/xml/lamp.xml");
    m_pGameObjectManager->SetGameObjectGUID(pLamp, "lamp");
	pLamp->GetTransform().Scale(glm::vec3(0.4f, 0.4, 0.4f));
	ComponentRigidBody* pLampRigid = static_cast<ComponentRigidBody*>(pLamp->GetComponent("GOC_RigidBody"));
	pLampRigid->BindGameObject();

	// Create ground
	Common::GameObject* pGround = m_pGameObjectManager->CreateGameObject("Assignment4/ExampleGame/data/xml/ground.xml");
	ComponentRigidBody* pGroundRigid = static_cast<ComponentRigidBody*>(pGround->GetComponent("GOC_RigidBody"));
	pGroundRigid->BindGameObject();

	// Create walls
	Common::GameObject* pWall1 = m_pGameObjectManager->CreateGameObject("Assignment4/ExampleGame/data/xml/wall.xml");
	m_pGameObjectManager->SetGameObjectGUID(pWall1, "wall1");
	pWall1->GetTransform().Rotate(glm::vec3(90.0f,0.0f,0.0f));
	pWall1->GetTransform().Translate(glm::vec3(0.0f,150.0f,75.0f));
	ComponentRigidBody* pWall1Rigid = static_cast<ComponentRigidBody*>(pWall1->GetComponent("GOC_RigidBody"));
	pWall1Rigid->BindGameObject();

	Common::GameObject* pWall2 = m_pGameObjectManager->CreateGameObject("Assignment4/ExampleGame/data/xml/wall.xml");
	m_pGameObjectManager->SetGameObjectGUID(pWall2, "wall2");
	pWall2->GetTransform().Rotate(glm::vec3(90.0f,0.0f,0.0f));
	pWall2->GetTransform().Translate(glm::vec3(0.0f,150.0f,-75.0f));
	ComponentRigidBody* pWall2Rigid = static_cast<ComponentRigidBody*>(pWall2->GetComponent("GOC_RigidBody"));
	pWall2Rigid->BindGameObject();

	Common::GameObject* pWall3 = m_pGameObjectManager->CreateGameObject("Assignment4/ExampleGame/data/xml/wall.xml");
	m_pGameObjectManager->SetGameObjectGUID(pWall3, "wall3");
	pWall3->GetTransform().Rotate(glm::vec3(90.0f,90.0f,0.0f));
	pWall3->GetTransform().Translate(glm::vec3(75.0f,150.0f,0.0f));
	ComponentRigidBody* pWall3Rigid = static_cast<ComponentRigidBody*>(pWall3->GetComponent("GOC_RigidBody"));
	pWall3Rigid->BindGameObject();

	Common::GameObject* pWall4 = m_pGameObjectManager->CreateGameObject("Assignment4/ExampleGame/data/xml/wall.xml");
	m_pGameObjectManager->SetGameObjectGUID(pWall4, "wall4");
	pWall4->GetTransform().Rotate(glm::vec3(90.0f,90.0f,0.0f));
	pWall4->GetTransform().Translate(glm::vec3(-75.0f,150.0f,0.0f));
	ComponentRigidBody* pWall4Rigid = static_cast<ComponentRigidBody*>(pWall4->GetComponent("GOC_RigidBody"));
	pWall4Rigid->BindGameObject();

	// Create timer
	Common::GameObject* pTimer = m_pGameObjectManager->CreateGameObject("Assignment4/ExampleGame/data/xml/timer.xml");
	m_pGameObjectManager->SetGameObjectGUID(pTimer, "timer");

	// HUD
	TFont tfont = TFont("Assignment4/ExampleGame/data/font/bm_0.tga","Assignment4/ExampleGame/data/font/bm.fnt");
	string txt = std::string("Score: 0");
	TTextBox* textbox1 = new TTextBox(&tfont,txt,	160, 40);
	textbox1->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	textbox1->SetPos(50,50);
	textbox1->Init();
	Common::SceneManager::Instance()->AttachHUDTextBox(textbox1);
	
	// Create crates 
	for (int j = 0;j<4;j++)
	{
		float randX = (rand() % 60) - (rand() % 10);
		float randZ = (rand() % 60) - (rand() % 10);
		for (int i = 0; i < 9; ++i)
		{
			Common::GameObject* pCrate = m_pGameObjectManager->CreateGameObject("Assignment4/ExampleGame/data/xml/crate.xml");
			char buff[64];
			sprintf(buff, "Crate%d",j*9+ i);
			m_pGameObjectManager->SetGameObjectGUID(pCrate, buff);

			glm::vec3 vPosition;
			vPosition.x = randX;
			if (i==0||i==1)
				vPosition.y = 0.0f;
			else
				vPosition.y = i*3.0f;
			vPosition.z = randZ;
			pCrate->GetTransform().SetTranslation(vPosition);

			ComponentRigidBody* pCrateRigid = static_cast<ComponentRigidBody*>(pCrate->GetComponent("GOC_RigidBody"));
			pCrateRigid->BindGameObject();
		}
	}

	// create button
	m_pButton  = m_pGameObjectManager->CreateGameObject("Assignment4/ExampleGame/data/xml/button_pause.xml");
	m_pButton->GetTransform().SetTranslation(glm::vec3(1125.0f, 0.0f, 0.0f));
}

void GamePlayState::Update(float p_fDelta)
{
	Common::BulletPhysicsManager::Instance()->Update(p_fDelta);

	static bool bLastKeyDown = false;
	bool bCurrentKeyDown = glfwGetKey('Z');
	if (bCurrentKeyDown && !bLastKeyDown)
	{
		Common::BulletPhysicsManager::Instance()->ToggleDebugRendering();
	}
	bLastKeyDown = bCurrentKeyDown;

	ComponentMouseClick *pMouse = static_cast<ComponentMouseClick*>(m_pButton->GetComponent("GOC_MouseClick"));
	if (pMouse->GetClicked())
	{
		pMouse->SetActive(false);
		m_pStateMachine->PushState(eStateGame_Pause);
	}
}

void GamePlayState::Suspend()
{
	ComponentCharacterController* pController = static_cast<ComponentCharacterController*>(m_pGameObjectManager->GetGameObject("character")->GetComponent("GOC_CharacterController"));
	pController->SetActive(false);

	ComponentTimerLogic* pTimer = static_cast<ComponentTimerLogic*>(m_pGameObjectManager->GetGameObject("timer")->GetComponent("GOC_TimerLogic"));
	pTimer->SetActive(false);
}

void GamePlayState::Resume()
{
	ComponentMouseClick *pMouse = static_cast<ComponentMouseClick*>(m_pButton->GetComponent("GOC_MouseClick"));
	pMouse->SetActive(true);

	ComponentCharacterController* pController = static_cast<ComponentCharacterController*>(m_pGameObjectManager->GetGameObject("character")->GetComponent("GOC_CharacterController"));
	pController->SetActive(true);

	ComponentTimerLogic* pTimer = static_cast<ComponentTimerLogic*>(m_pGameObjectManager->GetGameObject("timer")->GetComponent("GOC_TimerLogic"));
	pTimer->SetActive(true);
}

void GamePlayState::Exit()
{
	m_pGameObjectManager->DestroyGameObject(m_pButton);
}