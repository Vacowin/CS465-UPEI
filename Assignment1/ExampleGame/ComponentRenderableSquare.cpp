#include "ComponentRenderableSquare.h"
#include "GameObject.h"

void ComponentRenderableSquare::Init(const std::string &p_strTexturePath, const std::string &p_strVertexProgramPath, const std::string &p_strFragmentProgramPath,float x, float y, float z)
{
	m_pSquare = new Common::Square(p_strTexturePath, p_strVertexProgramPath, p_strFragmentProgramPath,x,y,z);
	Common::SceneManager::Instance()->AddSquareTexture(m_pSquare);
}

void ComponentRenderableSquare::SyncTransform()
{
	m_pSquare->SetTransform(this->GetGameObject()->GetTransform().GetTransformation());
}