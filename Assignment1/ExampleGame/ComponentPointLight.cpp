#include "ComponentPointLight.h"
#include "SceneManager.h"
#include "GameObject.h"

namespace Common
{
ComponentPointLight::ComponentPointLight()
{
	m_pPointLight = new PointLight();
	Common::SceneManager::Instance()->AddPointLight(m_pPointLight);
}

ComponentPointLight::~ComponentPointLight(void)
{
	delete m_pPointLight;
}

void ComponentPointLight::SyncTransform()
{
	m_pPointLight->m_vPosition = this->GetGameObject()->GetTransform().GetTranslation();

}
}