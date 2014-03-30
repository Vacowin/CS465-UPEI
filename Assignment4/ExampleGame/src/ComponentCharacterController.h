//------------------------------------------------------------------------
// ComponentCharacterController
//
// Created:	2012/12/14
// Author:	Carel Boers
//	
// This class implements a character controller. It polls input and sends
// movement instructions to the relevant sibling components.
//------------------------------------------------------------------------

#ifndef COMPNENTCHARACTERCONTROLLER_H
#define COMPNENTCHARACTERCONTROLLER_H

#include "ComponentBase.h"
#include "tinyxml\tinyxml.h"
#include "BaseEvent.h"
#include "glm\glm.hpp"

namespace week2
{
	class ComponentCharacterController : public Common::ComponentBase
	{
	public:
		//------------------------------------------------------------------------------
		// Public types.
		//------------------------------------------------------------------------------

	public:
		//------------------------------------------------------------------------------
		// Public methods.
		//------------------------------------------------------------------------------
		ComponentCharacterController();
		virtual ~ComponentCharacterController();

		virtual const std::string FamilyID() { return std::string("GOC_CharacterController"); }
		virtual const std::string ComponentID(){ return std::string("GOC_CharacterController"); }
		virtual void Update(float p_fDelta);

		const glm::vec3& getFaceDirection() { return m_vFace;}
		static Common::ComponentBase* CreateComponent(TiXmlNode* p_pNode);
		void SetActive(bool value) {m_bActive = value;}
	private:
		//------------------------------------------------------------------------------
		// Private members.
		//------------------------------------------------------------------------------

		// Keys buffer
		bool m_bKeysDown[256];
		bool m_bKeysDownLast[256];

		bool m_bTurnBack;
		bool m_bSKey;

		bool m_bToggleCamera;
		bool m_b3PCamera;

		float m_fRotateSpeed;
		float m_fSpeed;

		bool m_bToggleShoot;

		glm::vec3 m_vFace;
		bool m_bActive;
		
		long double m_numProjectiles;
	};
}

#endif // COMPNENTCHARACTERCONTROLLER_H

