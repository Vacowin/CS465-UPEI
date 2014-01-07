//------------------------------------------------------------------------
// ExampleGame
//
// Created:	2012/12/06
// Author:	Carel Boers
//	
// Main game class. Derives from Common::Game.
//------------------------------------------------------------------------

#ifndef WEEK1_EXAMPLEGAME_H
#define WEEK1_EXAMPLEGAME_H

#include "common/Game.h"
#include "W_Model.h"

namespace week1
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

		wolf::Model* m_pModel;
	};

} // namespace test

#endif // WEEK1_EXAMPLEGAME_H
