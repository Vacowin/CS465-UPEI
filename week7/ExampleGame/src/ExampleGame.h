//------------------------------------------------------------------------
// ExampleGame
//
// Created:	2012/12/06
// Author:	Carel Boers
//	
// Main game class. Derives from Common::Game.
//------------------------------------------------------------------------

#ifndef WEEK7_EXAMPLEGAME_H
#define WEEK7_EXAMPLEGAME_H

#include "common/Game.h"
#include "common/GameObjectManager.h"
#include "common/SceneCamera.h"

#include <list>

namespace week7
{
	class ExampleGame : public Common::Game
	{
	public:
		//------------------------------------------------------------------------------
		// Public methods.
		//------------------------------------------------------------------------------
		ExampleGame();
		virtual ~ExampleGame();

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

		// A camera for the scene
		Common::SceneCamera* m_pSceneCamera;
		
		// Game Object Manager
		Common::GameObjectManager* m_pGameObjectManager;
	};

} // namespace week7

#endif // WEEK7_EXAMPLEGAME_H
