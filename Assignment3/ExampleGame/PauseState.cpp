#include "PauseState.h"
#include "Assignment3/ExampleGame/ComponentRenderableSprite.h"
#include "Assignment3/ExampleGame/src/ExampleGame.h"
#include "Assignment3/ExampleGame/ComponentMouseClick.h"

using namespace week2;

PauseState::PauseState()
{
}


PauseState::~PauseState()
{
}

void PauseState::Enter()
{
	m_pButton  = ExampleGame::GetInstance()->GameObjectManager()->CreateGameObject("Assignment3/ExampleGame/data/xml/button_resume.xml");
	m_pButton->GetTransform().SetTranslation(glm::vec3(1125.0f, 0.0f, 0.0f));
}

void PauseState::Update(float p_fDelta)
{
	ComponentMouseClick *pMouse = static_cast<ComponentMouseClick*>(m_pButton->GetComponent("GOC_MouseClick"));
	if (pMouse->GetClicked())
	{
		m_pStateMachine->PopState();;
	}
}

void PauseState::Exit()
{
	ExampleGame::GetInstance()->GameObjectManager()->DestroyGameObject(m_pButton);
}

void PauseState::Suspend()
{
}

void PauseState::Resume()
{
}