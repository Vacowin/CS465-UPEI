#ifndef COMPONENTCOINLIFE_H
#define COMPONENTCOINLIFE_H

#include "ComponentBase.h"
#include "tinyxml\tinyxml.h"

namespace week2
{
	class ComponentCoinLife : public Common::ComponentBase
	{
	public:
		ComponentCoinLife(){};//float p_fLife) { m_fLifeSpan = p_fLife; }
		virtual ~ComponentCoinLife(){};

		virtual const std::string FamilyID() { return std::string("GOC_LifeSpan"); }
		virtual const std::string ComponentID(){ return std::string("GOC_LifeSpan"); }

		static Common::ComponentBase* CreateComponent(TiXmlNode* p_pNode);

		virtual void Update(float p_fDelta);

		void SetLifeSpan(float p_fLife) {m_fLifeSpan = p_fLife;}
		float GetLifeSpan() {return m_fLifeSpan;}
		void SetActive(bool value) { m_bActive = value;}
	private:
		float m_fLifeSpan;
		float m_fTimePassed;
		bool m_bActive;
	};
}

#endif