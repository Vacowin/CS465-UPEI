
#ifndef COMPONENTCOINMOVEMENT_H
#define COMPONENTCOINMOVEMENT_H

#include "ComponentBase.h"
#include "tinyxml\tinyxml.h"

namespace week2
{
	class ComponentCoinMovement : public Common::ComponentBase
	{
	public:
		ComponentCoinMovement(){m_iBobFlag = 1; m_fBob = 0;};
		virtual ~ComponentCoinMovement(){};

		virtual const std::string FamilyID() { return std::string("GOC_CoinMovement"); }
		virtual const std::string ComponentID(){ return std::string("GOC_CoinMovement"); }
		virtual void Update(float p_fDelta);

		static Common::ComponentBase* CreateComponent(TiXmlNode* p_pNode);

		void SetRotationSpeed(float p_fRotate) {m_fRotate = p_fRotate;}
		void SetBobScale(float p_fScale) {m_fBobScale = p_fScale;}
	private:
		float m_fRotate;
		float m_fBob;
		int m_iBobFlag;

		float m_fBobScale;
	};
}
#endif
