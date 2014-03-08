#ifndef DEFINE_TTEXTBOX
#define DEFINE_TTEXTBOX

#include <GL/glew.h>
#include <GL/glfw.h>

#include <cstdio>
#include <cstdarg>

#include "W_BufferManager.h"
#include "W_VertexDeclaration.h"
#include "W_ProgramManager.h"
#include "W_TextureManager.h"

#include "TFont.h"
#include "Assignment3\ExampleGame\BaseEvent.h"

struct Vertex
{
	inline Vertex(){}
	inline Vertex( GLfloat x1, GLfloat y1, GLfloat z1, GLfloat u1, GLfloat v1, GLfloat nx1, GLfloat ny1, GLfloat nz1 ) 
		{ x = x1; y = y1; z = z1; u = u1; v = v1; nx = nx1; ny = ny1; nz = nz1; }
	GLfloat x,y,z;
	GLfloat u,v;
	GLfloat nx, ny, nz;
};

enum THAlignment
{
	AL_Left = 0,
	AL_HCenter,
	AL_Right
};

enum TVAlignment
{
	AL_Top = 0,
	AL_VCenter,
	AL_Bottom
};

class TTextBox
{
public:
	TTextBox(){};
	TTextBox(TFont *p_pFont, const std::string& p_strText, unsigned int p_uiWidth, unsigned int p_uiHeight);
	void SetPos(int p_iXPos, int p_iYPos);
	void SetHorizontalAlignment(int p_Al);
	void SetColor(float p_fRed, float p_fGreen, float p_fBlue, float p_fAlpha);
	void SetHorizontalAlignment(THAlignment al);
	void SetVerticalAlignment(TVAlignment al);
	void SetText(const char *fmt, ...);

	void Init();
	void Render();

private:
	
	void ConstructQuadforChar(unsigned int p_uiCharID);
	void ConstructQuadforTextBox();
	int CalculateWordSpace(int p_index1, int *p_index2);
	int CalculateLineWidth(int p_index1, int p_index2);
	void RightCenterAlignment();
	void LeftAlignment();

	void EstimateTextLength(int *p_iX, int *p_iY);
	void ShrinkUntilFit();

	void HandleCoinCollected(BaseEvent* p_pBaseEvent);

	 TFont *m_pFont;
	 std::string m_strText;
	 glm::vec4 m_fontcolor;
	 unsigned int m_uiWidth;
	 unsigned int m_uiHeight;

	 unsigned int m_uiOriginXPos;
	 unsigned int m_uiOriginYPos;

	 unsigned int m_uiCurrentXPos;
	 unsigned int m_uiCurrentYPos;

	 int m_iXBoxOffset1, m_iXBoxOffset2, m_iYBoxOffset1, m_iYBoxOffset2;

	 int m_iIndexNewLine;
	 THAlignment m_HAlignment;
	 TVAlignment m_VAlignment;
	 float m_fSize;
	 int m_iTextHeight;

	 Vertex* m_pVertices;
	 unsigned int m_uiNumVertex;

	 wolf::VertexBuffer* m_pVertexBuffer;
	 wolf::VertexDeclaration* m_pVertexDeclaration;
	 wolf::Program* m_pProgram;
	 wolf::Texture* m_pTextureTextBox;
	 wolf::Texture* m_pTextureFont;


	 int m_iScore;
};
#endif