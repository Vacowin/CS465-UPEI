
#include "ComponentBase.h"
#include "SceneCamera.h"

namespace week2
{
class ComponentCamera : public Common::ComponentBase
{
public:
	ComponentCamera(float p_fFOV, float p_fAspectRatio, float p_fNearClip, float p_fFarClip, const glm::vec3 &p_vPos, const glm::vec3& p_vTarget, const glm::vec3& p_vUp);
	virtual ~ComponentCamera(){};

	virtual const std::string ComponentID(){ return std::string("GOC_Camera"); }
	virtual void Update(float p_fDelta) ;
	virtual const std::string FamilyID() { return std::string("GOC_Camera"); }

	Common::SceneCamera* GetCamera() {return m_pCamera;}

private:
	Common::SceneCamera *m_pCamera;
};
}
