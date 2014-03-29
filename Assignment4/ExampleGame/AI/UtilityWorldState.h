
#ifndef UTILITYWORLDSTATE_H
#define UTILITYWORLDSTATE_H

#include <glm/glm.hpp>
#include <string>
#include "common\GameObject.h"
#include "Assignment4/ExampleGame/ComponentAIController.h"

using namespace Common;
using namespace week2;

namespace week2
{
	class UtilityWorldState
	{
	public:
		UtilityWorldState();
		~UtilityWorldState();

		void ApplyAction(AIState p_eStateAction);
		float Utility(GameObject* p_pGameObject);
		static UtilityWorldState* Copy();

	private:
		AIState m_eStateAction;
		GameObject* m_pCharacter;

		GameObject* m_pZombieCharacter;
		GameObject* m_pZombieCoin1;
		GameObject* m_pZombieCoin2;

		std::string m_sCoinID1;
		std::string m_sCoinID2;

	};
}

#endif 

