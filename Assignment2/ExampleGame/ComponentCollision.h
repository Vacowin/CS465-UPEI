#ifndef COMPONENTCOLLISION_H
#define COMPONENTCOLLISION_H

#include "ComponentBase.h"
#include "tinyxml\tinyxml.h"

namespace week2
{
	class ComponentCollision : public Common::ComponentBase
	{
	public:
		ComponentCollision(){};//float p_fRadius) { m_fBoundingRadius = p_fRadius; }
		virtual ~ComponentCollision(){};

		virtual const std::string FamilyID() { return std::string("GOC_CollisionSphere"); }
		virtual const std::string ComponentID(){ return std::string("GOC_CollisionSphere"); }
		virtual void Update(float p_fDelta);

		static Common::ComponentBase* CreateComponent(TiXmlNode* p_pNode);

		void SetRadius(float p_fRadius) {m_fBoundingRadius = p_fRadius;}
		float GetRadius() {return m_fBoundingRadius;}
	private:
		float m_fBoundingRadius;
	};
}

#endif