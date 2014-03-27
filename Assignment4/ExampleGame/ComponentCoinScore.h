#ifndef COMPONENTCOINSCORE_H
#define COMPONENTCOINSCORE_H

#include "ComponentBase.h"
#include "tinyxml\tinyxml.h"

namespace week2
{
	class ComponentCoinScore : public Common::ComponentBase
	{
	public:
		ComponentCoinScore(){};//)int p_iScore) { m_iScore = p_iScore; }
		virtual ~ComponentCoinScore(){};

		virtual const std::string FamilyID() { return std::string("GOC_CoinScore"); }
		virtual const std::string ComponentID(){ return std::string("GOC_CoinScore"); }

		static Common::ComponentBase* CreateComponent(TiXmlNode* p_pNode);

		int GetScore() {return m_iScore;}
		void SetScore(int p_iScore);// {m_iScore = p_iScore;}
	private:
		int m_iScore;
	};
}

#endif