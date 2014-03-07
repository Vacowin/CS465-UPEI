#ifndef DEFINE_TFONT
#define DEFINE_TFONT

#include "W_Common.h"
#include "W_TextureManager.h"
#include <string>
using namespace std;

struct CharDescriptor
{
	unsigned short x, y;
	unsigned short Width, Height;
	short XOffset, YOffset;
	unsigned short XAdvance;
	unsigned short Page;

	CharDescriptor() : x( 0 ), y( 0 ), Width( 0 ), Height( 0 ), XOffset( 0 ), YOffset( 0 ),
		XAdvance( 0 ), Page( 0 )
	{ }
};

struct Charset
{
	unsigned short LineHeight;
	unsigned short Base;
	unsigned short Width, Height;
	unsigned short Pages;
	CharDescriptor Chars[256];
};

class TFont
{
public:
	TFont(const std::string& p_strTexture, const std::string& p_strDescription);
	void GetExtentsForChar(unsigned int p_uiCharId,float *p_uStart,float *p_uEnd,float *p_vStart,float *p_vEnd,
		unsigned int *p_uiWidth, unsigned int *p_uiHeight, unsigned int *p_uiXAdvance, int *p_uiXOffset, int *p_uiYOffset);
	wolf::Texture* GetTextureForChar(unsigned int p_uiCharId);
	int GetCharAdvance(unsigned int p_uiCharId);
	int GetCharHeight(unsigned int p_uiCharId);

	Charset m_Charset;

private:
	wolf::Texture* m_pTexture;
};
#endif