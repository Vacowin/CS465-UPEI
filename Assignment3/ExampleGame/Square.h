// Class used to render a texture square

#ifndef SQUARE_H
#define SQUARE_H
#include "W_BufferManager.h"
#include "W_TextureManager.h"
#include "W_MaterialManager.h"
#include "W_VertexDeclaration.h"

namespace Common
{
struct Vertex
{
	GLfloat x,y,z;
	GLfloat u,v;
	GLfloat nx, ny, nz;
};

class Square
{
public:
	Square(const std::string& p_strTexturePath, const std::string& p_strVertexProgram, const std::string& p_strFragmentProgram, float x, float y, float z);
	~Square();
	void Render(const glm::mat4& p_mView, const glm::mat4& p_mProj);
	wolf::Material* GetMaterial() { return m_pMaterial; }
	void SetTransform(const glm::mat4& p_mWorldTransform) { m_mWorldTransform = p_mWorldTransform; }

private:
	wolf::Material* m_pMaterial;
	glm::mat4 m_mWorldTransform;
	wolf::VertexDeclaration* m_pVertexDeclaration;
	wolf::Texture* m_pTexture;
};

}
#endif