#include "TTextBox.h"
#include "Assignment2\ExampleGame\EventManager.h"
#include "Assignment2\ExampleGame\EventCoinCollected.h"
#include "common\GameObject.h"
#include "Assignment2\ExampleGame\ComponentCoinScore.h"

#define NEW_LINE 40

TTextBox::TTextBox(TFont *p_pFont, const std::string& p_strText, unsigned int p_uiWidth, unsigned int p_uiHeight)
{
	m_pProgram = NULL;
	m_pTextureFont = m_pTextureTextBox = NULL;
	m_pFont = p_pFont;
	m_strText = p_strText;
	m_uiWidth = p_uiWidth;
	m_uiHeight = p_uiHeight;

	m_iXBoxOffset1 = 10 * (m_uiWidth/256.0);
	m_iYBoxOffset1 = 10 * (m_uiHeight/256.0);

	m_pVertices = new Vertex[10000];
	m_uiNumVertex = 0;

	m_HAlignment = AL_Left;
	m_VAlignment = AL_Top;
	m_fSize = 1.1f;
	m_iTextHeight = 0;

	m_iScore = 0;

	EventListener eventListener1 = std::tr1::bind(&TTextBox::HandleCoinCollected, this, std::tr1::placeholders::_1);
	EventManager::Instance()->AddListener(Event_CoinCollected, eventListener1);

}

int TTextBox::CalculateWordSpace(int p_index1, int *p_index2)
{
	unsigned int space=0;
	int i;
	for (i=p_index1;i<m_strText.size();i++)
	{
		if (m_strText[i] == 32)
			break;

		space += m_fSize * m_pFont->GetCharAdvance(m_strText[i]);
	}
	*p_index2 = i-1;
	return space;
}

int TTextBox::CalculateLineWidth(int p_index1, int p_index2)
{
	int space=0;
	for (int i=p_index1;i<= p_index2;i++)
	{
		space +=  m_fSize * m_pFont->GetCharAdvance(m_strText[i]);
	}
	return space;
}

void TTextBox::ConstructQuadforChar(unsigned int p_uiCharID)
{
	float fUstart, fUend, fVstart, fVend;
	unsigned int uiWidth, uiHeight, uiXAdvance;
	int iXOffset, iYOffset;

	m_pFont->GetExtentsForChar(p_uiCharID, &fUstart, &fUend, &fVstart, &fVend, &uiWidth, &uiHeight, &uiXAdvance, &iXOffset, &iYOffset);

	m_pVertices[m_uiNumVertex++] = Vertex(m_uiCurrentXPos + iXOffset, m_iTextHeight+ m_uiCurrentYPos + iYOffset, 0 , fUstart, fVstart,    0,0,0);
	m_pVertices[m_uiNumVertex++] = Vertex(m_uiCurrentXPos + iXOffset, m_iTextHeight+ m_uiCurrentYPos + uiHeight*m_fSize , 0 , fUstart, fVend,    0,0,0);
	m_pVertices[m_uiNumVertex++] = Vertex(m_uiCurrentXPos + uiWidth*m_fSize, m_iTextHeight+ m_uiCurrentYPos + uiHeight*m_fSize, 0, fUend, fVend,   0,0,0);
	m_pVertices[m_uiNumVertex++] = Vertex(m_uiCurrentXPos + uiWidth*m_fSize, m_iTextHeight+ m_uiCurrentYPos + uiHeight*m_fSize, 0, fUend, fVend,   0,0,0);
	m_pVertices[m_uiNumVertex++] = Vertex(m_uiCurrentXPos + uiWidth*m_fSize, m_iTextHeight+ m_uiCurrentYPos + iYOffset, 0, fUend, fVstart,   0,0,0);
	m_pVertices[m_uiNumVertex++] = Vertex(m_uiCurrentXPos + iXOffset, m_iTextHeight+ m_uiCurrentYPos + iYOffset, 0 , fUstart, fVstart,   0,0,0);

	m_uiCurrentXPos += uiXAdvance*m_fSize;
}

void TTextBox::ConstructQuadforTextBox()
{
	m_pVertices[m_uiNumVertex++] = Vertex(m_uiOriginXPos , m_uiOriginYPos , 0 , 0, 1,    0,0,0);
	m_pVertices[m_uiNumVertex++] = Vertex(m_uiOriginXPos , m_uiOriginYPos + m_uiHeight , 0 , 0, 0,    0,0,0);
	m_pVertices[m_uiNumVertex++] = Vertex(m_uiOriginXPos + m_uiWidth, m_uiOriginYPos + m_uiHeight, 0, 1, 0,   0,0,0);
	m_pVertices[m_uiNumVertex++] = Vertex(m_uiOriginXPos + m_uiWidth, m_uiOriginYPos + m_uiHeight, 0, 1, 0,   0,0,0);
	m_pVertices[m_uiNumVertex++] = Vertex(m_uiOriginXPos + m_uiWidth, m_uiOriginYPos , 0, 1, 1,   0,0,0);
	m_pVertices[m_uiNumVertex++] = Vertex(m_uiOriginXPos , m_uiOriginYPos, 0 , 0, 1,   0,0,0);
}

void TTextBox::Init()
{
	m_pFont = new TFont("assignment2/ExampleGame/data/font/bm_0.tga","assignment2/ExampleGame/data/font/bm.fnt");
	m_uiCurrentXPos = m_uiOriginXPos + m_iXBoxOffset1;
	m_iXBoxOffset1 = 10 * (m_uiWidth/256.0);
	m_iYBoxOffset1 = 10 * (m_uiHeight/256.0);

	m_pVertices = new Vertex[10000];
	m_uiNumVertex = 0;

	m_HAlignment = AL_Left;
	m_VAlignment = AL_Top;
	m_fSize = 1.1f;
	m_iTextHeight = 0;

	ConstructQuadforTextBox();

	ShrinkUntilFit();
	
	if (m_VAlignment == AL_Top)
		m_iTextHeight = 0;
	else 
	{
		m_iTextHeight = m_uiHeight - m_iYBoxOffset1*2 - m_iTextHeight;
		if (m_VAlignment == AL_VCenter)
			m_iTextHeight /= 2;
	}

	if (m_HAlignment != AL_Left)
	{
		RightCenterAlignment();
		return;
	}

	// auto left alignment
	int index;
	for (int i=0; i<m_strText.size(); i++)
	{
		char ch = m_strText[i];
		if (i>0)
		{
			if (ch=='F') 
				printf("sdsd");
			if (ch != 32 && m_strText[i-1] == 32 )
			{
				int dif = (m_uiOriginXPos + m_uiWidth) - m_uiCurrentXPos - m_iXBoxOffset1;
				int space = CalculateWordSpace(i,&index);
				if (space > dif)
				{
					m_uiCurrentXPos = m_uiOriginXPos + m_iXBoxOffset1;
					m_uiCurrentYPos += NEW_LINE*m_fSize;
					m_iIndexNewLine = i;
				}
			}
		}
		ConstructQuadforChar(ch);
	}

	if (!m_pProgram)
		m_pProgram = wolf::ProgramManager::CreateProgram("Assignment2/ExampleGame/data/font/one_texture.vsh", "Assignment2/ExampleGame/data/font/one_texture.fsh");
	m_pVertexBuffer = wolf::BufferManager::CreateVertexBuffer(m_pVertices,sizeof(Vertex) * m_uiNumVertex);

	m_pVertexDeclaration = new wolf::VertexDeclaration();
	m_pVertexDeclaration->Begin();
	m_pVertexDeclaration->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
	m_pVertexDeclaration->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
	m_pVertexDeclaration->AppendAttribute(wolf::AT_Normal, 3, wolf::CT_Float);
	m_pVertexDeclaration->SetVertexBuffer(m_pVertexBuffer);
	m_pVertexDeclaration->End();

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
	if (!m_pTextureTextBox)
		m_pTextureTextBox = wolf::TextureManager::CreateTexture("Assignment2/ExampleGame/data/font/textbox.tga");
	if (!m_pTextureFont)
		m_pTextureFont = m_pFont->GetTextureForChar(0);
}

void TTextBox::RightCenterAlignment()
{
	int wordindex, lineindex1=0, lineindex2;
	int dif;
	int tempX = m_uiCurrentXPos;
	for (int i=0; i<m_strText.size(); i++)
	{
		char ch = m_strText[i];
		if (i>0)
		{
			if (ch=='F') 
				printf("sdsd");
			if (ch != 32 && m_strText[i-1] == 32 )
			{
				dif = (m_uiOriginXPos + m_uiWidth) - tempX - m_iXBoxOffset1;
				int space = CalculateWordSpace(i, &wordindex);
				
				if ((space > dif) )
				{
					lineindex2 = i-1;
					int tempwidth = CalculateLineWidth(lineindex1, lineindex2);
					m_uiCurrentXPos = m_uiOriginXPos - m_iXBoxOffset1 + (m_uiWidth - tempwidth);

					// center alignment
					if (m_HAlignment == AL_HCenter)
						m_uiCurrentXPos = m_uiOriginXPos + (m_uiWidth - tempwidth)/2;

					for (int j=lineindex1;j<=lineindex2;j++)
					{
						char ch1 = m_strText[j];
						ConstructQuadforChar(ch1);
					}

					m_uiCurrentXPos = m_uiOriginXPos + m_iXBoxOffset1;
					m_uiCurrentYPos += m_fSize * NEW_LINE;	
					lineindex1 = i;
					tempX = m_uiOriginXPos + m_iXBoxOffset1;
				}
			}
			if (i == m_strText.size()-1)
			{
				lineindex2 = m_strText.size()-1;
				int tempwidth = CalculateLineWidth(lineindex1, lineindex2);

				m_uiCurrentXPos = m_uiOriginXPos - m_iXBoxOffset1 + (m_uiWidth - tempwidth);
				// center alignment
				if (m_HAlignment == AL_HCenter)
					m_uiCurrentXPos = m_uiOriginXPos  + (m_uiWidth - tempwidth)/2;

				for (int j=lineindex1;j<=lineindex2;j++)
				{
					char ch1 = m_strText[j];
					ConstructQuadforChar(ch1);
				}
			}
			tempX+= m_fSize * m_pFont->GetCharAdvance(ch);
		}
	}
}

void TTextBox::SetHorizontalAlignment(THAlignment al)
{
	m_HAlignment = al;
}

void TTextBox::SetVerticalAlignment(TVAlignment al)
{
	m_VAlignment = al;
}

void TTextBox::SetColor(float p_fRed, float p_fBlue, float p_fGreen, float p_fAlpha)
{
	m_fontcolor = glm::vec4(p_fRed, p_fBlue, p_fGreen, p_fAlpha);
}

void TTextBox::SetPos(int p_iXPos, int p_iYPos)
{
	m_uiOriginXPos = p_iXPos;
	m_uiOriginYPos = p_iYPos;
	m_uiCurrentXPos = m_uiOriginXPos + m_iXBoxOffset1;
	m_uiCurrentYPos = m_uiOriginYPos + m_iYBoxOffset1;

}

void TTextBox::Render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_pProgram->Bind();
	m_pVertexDeclaration->Bind();

    glm::mat4 mProj = glm::ortho(0.0f,1280.0f,720.0f,0.0f,0.0f,1000.0f);
	m_pProgram->SetUniform("projection", mProj);

	// draw box
	m_pProgram->SetUniform("fontcolor", glm::vec4(1.0f,1.0f,1.0f,1.0f));
	m_pTextureTextBox->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// draw characters
	m_pProgram->SetUniform("fontcolor", m_fontcolor);
	m_pTextureFont->Bind();
	glDrawArrays(GL_TRIANGLES, 6, m_uiNumVertex-6);

	glDisable(GL_BLEND);
}

void TTextBox::EstimateTextLength(int *p_iX, int *p_iY)
{
	int index;
	*p_iX = m_uiCurrentXPos;
	*p_iY = m_uiCurrentYPos;

	int i;
	for (i=0; i<m_strText.size(); i++)
	{
		char ch = m_strText[i];
		if (i>0)
		{
			if (ch=='F') 
				printf("sdsd");
			if (ch != 32 && m_strText[i-1] == 32 )
			{
				int dif = (m_uiOriginXPos + m_uiWidth) - *p_iX - m_iXBoxOffset1;
				int space = CalculateWordSpace(i,&index);
				if (space > dif)
				{
					*p_iX = m_uiOriginXPos + m_iXBoxOffset1;
					*p_iY += m_fSize * NEW_LINE;
					m_iIndexNewLine = i;
				}
			}
		}

		*p_iX += m_fSize * m_pFont->GetCharAdvance(ch);
	}
	if (i>0)
		*p_iY += m_fSize * m_pFont->GetCharHeight(m_strText[i-1]);

	m_iTextHeight = *p_iY - m_uiOriginYPos - m_iYBoxOffset1;
}

void TTextBox::ShrinkUntilFit()
{
	int estX = m_uiCurrentXPos;
	int estY = m_uiCurrentYPos;

	do {
		m_fSize -= 0.1f;
		if (m_fSize == 0.0f) break;
		EstimateTextLength(&estX, &estY);
	}
	while ((estX > m_uiOriginXPos+ m_uiWidth - 2*m_iXBoxOffset1) || (estY > m_uiOriginYPos + m_uiHeight - 2*m_iYBoxOffset1));
}

void TTextBox::SetText(const char *format, ...)
{
    va_list arg_list;                                                           
    va_start(arg_list, format);                                                 

    char short_buf[256];                                                        
    const size_t needed = vsnprintf(short_buf, sizeof short_buf,
                                    format, arg_list) + 1;
    if (needed <= sizeof short_buf)
	{
		m_strText = short_buf;
        return;
	}

    char* p = static_cast<char*>(alloca(needed));
    vsnprintf(p, needed, format, arg_list);
    m_strText = p;
}

void TTextBox::HandleCoinCollected(BaseEvent* p_pBaseEvent)
{
	EventCoinCollected *pEventCoinCollected = static_cast<EventCoinCollected*>(p_pBaseEvent);
	Common::GameObject *pCoin = pEventCoinCollected->GetCoin();
	week2::ComponentCoinScore *pScoreComponent = static_cast<week2::ComponentCoinScore*>( pCoin->GetComponent("GOC_CoinScore"));

	m_iScore += pScoreComponent->GetScore();
	Init();
	this->SetText("Score: %d",m_iScore);
}