
#include "ComponentBase.h"
#include "SceneCamera.h"

namespace week2
{
class ComponentCamera : public Common::ComponentBase
{
public:
	ComponentCamera();
	virtual ~ComponentCamera(){};

	virtual const std::string ComponentID(){ return std::string("GOC_Camera"); }
	virtual void Update(float p_fDelta) ;
	virtual const std::string FamilyID() { return std::string("GOC_Camera"); }

	void SetCamera(Common::SceneCamera* p_pCamera);
	Common::SceneCamera* GetCamera() {return m_pCamera;}

private:
	Common::SceneCamera *m_pCamera;
};
}
