//------------------------------------------------------------------------
// ExampleGame
//
// Created:	2012/12/06
// Author:	Carel Boers
//	
// Main game class. Derives from Common::Game.
//------------------------------------------------------------------------

#ifndef WEEK2_EXAMPLEGAME_H
#define WEEK2_EXAMPLEGAME_H

#include "common/Game.h"
#include "common/GameObjectManager.h"
#include "common/SceneCamera.h"
#include "common\StateMachine.h"
#include <list>

namespace week2
{
	class ExampleGame : public Common::Game
	{
	public:
		//------------------------------------------------------------------------------
		// Public methods.
		//------------------------------------------------------------------------------
		ExampleGame();
		virtual ~ExampleGame();

		// Static instance
		static ExampleGame* GetInstance() { return s_pInstance; }
		Common::GameObjectManager* GameObjectManager() { 
			return m_pGameObjectManager; }

	protected:	
		//------------------------------------------------------------------------------
		// Protected methods.
		//------------------------------------------------------------------------------
		virtual bool Init();
		virtual bool Update(float p_fDelta);
		virtual void Render();
		virtual void Shutdown();

	private:
		//------------------------------------------------------------------------------
		// Private members.
		//------------------------------------------------------------------------------
		static ExampleGame* s_pInstance;

		// A camera for the scene
		Common::SceneCamera* m_pSceneCamera;

		// Game Object Manager
		Common::GameObjectManager* m_pGameObjectManager;

		Common::StateMachine* m_pStateMachine;
	};

} // namespace week2

#endif // WEEK2_EXAMPLEGAME_H
