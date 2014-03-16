#pragma once
#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H
#include "common\StateBase.h"
#include "common/GameObjectManager.h"
#include "common/SceneCamera.h"

namespace week2
{
	class GamePlayState : public Common::StateBase
	{
	public:
		GamePlayState();
		~GamePlayState();

		virtual void Enter();
		virtual void Update(float p_fDelta);
		virtual void Exit();
		virtual void Suspend();
		virtual void Resume();

	private:
		Common::SceneCamera* m_pSceneCamera;
		Common::GameObjectManager* m_pGameObjectManager;
	};
}
#endif
