#ifndef COMPONENTTIMERLOGIC_H
#define COMPONENTTIMERLOGIC_H

#include "ComponentBase.h"
#include <vector>
#include "GameObject.h"
#include "EventObjectCollision.h"
#include "EventManager.h"
#include "tinyxml\tinyxml.h"
#include <string>

using namespace std;

namespace week2
{
	class ComponentTimerLogic : public Common::ComponentBase
	{
	public:
		ComponentTimerLogic();
		virtual ~ComponentTimerLogic(){};

		virtual const std::string FamilyID() { return std::string("GOC_TimerLogic"); }
		virtual const std::string ComponentID(){ return std::string("GOC_TimerLogic"); }
		virtual void Update(float p_fDelta);

		static Common::ComponentBase* CreateComponent(TiXmlNode* p_pNode);

		std::vector<Common::GameObject*> m_lCoinList;

		void SetMaxCoin(int p_iMax) {m_iMaxNumCoin = p_iMax;}
		void SetFrequency(float p_fFre) { m_fFrequency = p_fFre;}
		void SetDefaultObject(std::string p_sObject) { m_sObjectName = p_sObject;}
	private:
		void HandleCoinCollision(BaseEvent *p_Event);
		void HandleCoinDisappeared(BaseEvent *p_Event);

		int m_iMaxNumCoin;
		float m_fFrequency;
		float m_fTimePassed;
		std::string m_sObjectName;
		long double m_lNumCoin;
	};
}
#endif