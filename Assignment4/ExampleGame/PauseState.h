#pragma once
#ifndef PAUSETATE_H
#define PAUSESTATE_H
#include "common\StateBase.h"
#include "common\GameObject.h"

namespace week2
{
	class PauseState : public Common::StateBase
	{
	public:
		PauseState();
		~PauseState();

		virtual void Enter();
		virtual void Update(float p_fDelta);
		virtual void Exit();
		virtual void Suspend();
		virtual void Resume();
	private:
		Common::GameObject* m_pButton;
		Common::GameObject* m_pMessage;
	};
}
#endif
