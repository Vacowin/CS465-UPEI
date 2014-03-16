#pragma once
#ifndef COMPONENTMOUSECLICK_H
#define COMPONENTMOUSECLICK_H

#include "ComponentBase.h"
#include "tinyxml\tinyxml.h"

namespace week2
{
	class ComponentMouseClick: public Common::ComponentBase
	{
	public:
		ComponentMouseClick();
		virtual ~ComponentMouseClick();

		virtual const std::string FamilyID() { return std::string("GOC_MouseClick"); }
		virtual const std::string ComponentID(){ return std::string("GOC_MouseClick"); }

		static Common::ComponentBase* CreateComponent(TiXmlNode* p_pNode);

		virtual void Update(float p_fDelta);

		void SetWidth(float value) { m_fWidth = value;}
		void SetHeight(float value) { m_fHeight = value;}
		bool GetClicked() { return m_bIsClicked;}
		void SetActive(bool value) { m_bActive = value;}
		bool GetActive() { return m_bActive;}
	private:
		bool m_bActive;
		bool m_bIsClicked;
		bool m_bToogleClick;
		float m_fWidth;
		float m_fHeight;
	};
}
#endif
