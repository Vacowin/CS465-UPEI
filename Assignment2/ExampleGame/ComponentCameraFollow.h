
#include "ComponentBase.h"
#include "SceneCamera.h"

namespace week2
{
class ComponentCameraFollow : public Common::ComponentBase
{
public:
	ComponentCameraFollow(float p_fFOV, float p_fAspectRatio, float p_fNearClip, float p_fFarClip, const glm::vec3 &p_vPos, const glm::vec3& p_vTarget, const glm::vec3& p_vUp);
	virtual ~ComponentCameraFollow(){};

	virtual const std::string ComponentID(){ return std::string("GOC_CameraFollow"); }
	virtual void Update(float p_fDelta) ;
	virtual const std::string FamilyID() { return std::string("GOC_CameraFollow"); }

	Common::SceneCamera* GetCamera() {return m_pCamera;}

private:
	Common::SceneCamera *m_pCamera;
};
}
