
#ifndef STATELEADERBOARD_H
#define STATELEADERBOARD_H

#include "GameObject.h"
#include "StateBase.h"

namespace week6
{
	class StateLeaderBoard : public Common::StateBase
	{
	public:
		//------------------------------------------------------------------------------
		// Public methods.
		//------------------------------------------------------------------------------
		StateLeaderBoard();
		virtual ~StateLeaderBoard();

		// Overridden from StateBase
		virtual void Enter();
		virtual void Update(float p_fDelta);
		virtual void Exit();

	private:
		//------------------------------------------------------------------------------
		// Private members.
		//------------------------------------------------------------------------------

	};
} // namespace week6

#endif

