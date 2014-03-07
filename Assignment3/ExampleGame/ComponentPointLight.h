#ifndef COMPONENTPOINTLIGHT_H
#define COMPONENTPOINTLIGHT_H

#include "W_Types.h"
#include "ComponentBase.h"

namespace Common
{
struct PointLight
{
	glm::vec3		m_vPosition;
	glm::vec3		m_vAttenuation;
	float			m_fRange;
    wolf::Color4    m_ambient;
	wolf::Color4	m_diffuse;
	wolf::Color4	m_specular;
    PointLight() : m_fRange(0), m_diffuse(0,0,0,0), m_specular(0,0,0,0), m_ambient(0,0,0,0) {}    
};

class ComponentPointLight : public Common::ComponentBase
{
public:
	ComponentPointLight();
	~ComponentPointLight();

	void SetLightPos(const glm::vec3& p_vWorldPosition) { m_pPointLight->m_vPosition = p_vWorldPosition; }
    void SetLightDiffuse(wolf::Color4 p_cDiffuse) { m_pPointLight->m_ambient = p_cDiffuse; }
    void SetLightSpecular(wolf::Color4 p_cSpecular) { m_pPointLight->m_specular = p_cSpecular; }
    void SetLightAttenuation(glm::vec3 p_vAttenuation) { m_pPointLight->m_vAttenuation = p_vAttenuation; }
    void SetLightRange(float p_fRange) { m_pPointLight->m_fRange = p_fRange; }

	virtual const std::string FamilyID() { return std::string("GOC_PointLight"); }
    virtual const std::string ComponentID() { return std::string("GOC_PointLight"); }
    virtual void SyncTransform();

	PointLight* GetPointLight() {return m_pPointLight;};
private:
	PointLight *m_pPointLight;
};
}

#endif