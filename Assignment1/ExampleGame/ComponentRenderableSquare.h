#include "ComponentRenderable.h"
#include "SceneManager.h"
#include "Square.h"

class ComponentRenderableSquare : public Common::ComponentRenderable
{
public:
	ComponentRenderableSquare() {}
	virtual ~ComponentRenderableSquare() {}

	virtual const std::string ComponentID() { return std::string("GOC_RenderableSquare"); }
	virtual void Init(const std::string &p_strTexturePath, const std::string &p_strVertexProgramPath, const std::string &p_strFragmentProgramPath,float x, float y, float z);
	virtual void SyncTransform();

	Common::Square* GetSquare() {return m_pSquare;};

private:
    Common::Square* m_pSquare;
};

