
#ifndef STATECHASINGCOIN_H
#define STATECHASINGCOIN_H

#include "StateBase.h"
#include "GameObject.h"
#include <list>

namespace week2
{
	class AIStateChasingCoin : public Common::StateBase
	{
	public:
		//------------------------------------------------------------------------------
		// Public methods.
		//------------------------------------------------------------------------------
		AIStateChasingCoin();
		virtual ~AIStateChasingCoin();

		// Overridden from StateBase
		virtual void Enter();
		virtual void Update(float p_fDelta);
		virtual void Exit();
		virtual void Suspend() {};
		virtual void Resume(){};
	private:
		//------------------------------------------------------------------------------
		// Private members.
		//------------------------------------------------------------------------------

		// The GameObject we are chasing. Set when Enter() is called.
		Common::GameObject* m_pTargetGameObject;

		// Current path we are following
		std::list<glm::vec3> m_lPath;
	};
} // namespace week9

#endif // STATECHASING_H

