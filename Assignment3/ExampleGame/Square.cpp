#include "Square.h"


//}
namespace Common
{
Square::Square(const std::string& p_strTexturePath, const std::string& p_strVertexProgram, const std::string& p_strFragmentProgram,float x, float y, float z)
{
	wolf::Texture* pTex = wolf::TextureManager::CreateTexture(p_strTexturePath);
    pTex->SetWrapMode(wolf::Texture::WM_Repeat, wolf::Texture::WM_Repeat);
    m_pMaterial = wolf::MaterialManager::CreateMaterial("Square");
    m_pMaterial->SetTexture("texture", pTex);
    m_pMaterial->SetProgram(p_strVertexProgram, p_strFragmentProgram);

	
	float u = x/20;
	float v = z/20;

	Vertex vertices[] = { { -x, y, -z,    0.0f, 0.0f          , 0.0f, 1.0f, 0.0f},
	                      { -x, y,z,      0.0f, v             , 0.0f, 1.0f, 0.0f },
	                      {  x, y,z,      u, v                , 0.0f, 1.0f, 0.0f },
	                      {  x, y,z,      u, v                , 0.0f, 1.0f, 0.0f },
	                      {  x, y, -z,    u, 0.0f             , 0.0f, 1.0f, 0.0f },
                          { -x, y, -z,    0.0f, 0.0f          , 0.0f, 1.0f, 0.0f } };

	m_pVertexDeclaration = new wolf::VertexDeclaration();
	m_pVertexDeclaration->Begin();
	m_pVertexDeclaration->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
	m_pVertexDeclaration->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
	m_pVertexDeclaration->AppendAttribute(wolf::AT_Normal, 3, wolf::CT_Float);
	m_pVertexDeclaration->SetVertexBuffer(wolf::BufferManager::CreateVertexBuffer(vertices, sizeof(Vertex) * 6));
	m_pVertexDeclaration->End();
}

Square::~Square(void)
{
}

void Square::Render(const glm::mat4& p_mView, const glm::mat4& p_mProj)
{
	m_pVertexDeclaration->Bind();
    m_pMaterial->Apply();
    m_pMaterial->SetUniform("projection", p_mProj);
    m_pMaterial->SetUniform("view", p_mView);
    m_pMaterial->SetUniform("world", m_mWorldTransform);
    m_pMaterial->SetUniform("worldIT", glm::transpose(glm::inverse(m_mWorldTransform)));
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
}