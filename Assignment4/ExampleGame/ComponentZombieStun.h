#ifndef COMPONENTZOMBIESTUN_H
#define COMPONENTZOMBIESTUN_H

#include "ComponentBase.h"
#include "GameObject.h"
#include "tinyxml\tinyxml.h"
#include <string>
#include "BaseEvent.h"

using namespace std;

namespace week2
{
	class ComponentZombieStun : public Common::ComponentBase
	{
	public:
		ComponentZombieStun(float p_fDuration);
		virtual ~ComponentZombieStun(){};

		virtual const std::string FamilyID() { return std::string("GOC_ZombieStun"); }
		virtual const std::string ComponentID(){ return std::string("GOC_ZombieStun"); }
		virtual void Update(float p_fDelta);

		static Common::ComponentBase* CreateComponent(TiXmlNode* p_pNode);

		bool GetIsStunned() { return m_bIsStunned;}
	private:
		void HandleProjectileCollision(BaseEvent *p_Event);

		float m_fDuration;
		float m_fStunTime;
		bool m_bIsStunned;
	};
}
#endif