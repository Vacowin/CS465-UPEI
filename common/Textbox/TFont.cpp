
#include <sstream>
#include <fstream>

#include "TFont.h"

bool ParseFont(const std::string& p_strDescription, Charset& CharsetDesc )
{
	ifstream Stream (p_strDescription);
	string Line;
	string Read, Key, Value;
	std::size_t i;
	while( !Stream.eof() )
	{
		std::stringstream LineStream;
		std::getline( Stream, Line );
		LineStream << Line;

		LineStream >> Read;
		if( Read == "common" )
		{
			while( !LineStream.eof() )
			{
				std::stringstream Converter;
				LineStream >> Read;
				i = Read.find( '=' );
				Key = Read.substr( 0, i );
				Value = Read.substr( i + 1 );

				Converter << Value;
				if( Key == "lineHeight" )
					Converter >> CharsetDesc.LineHeight;
				else if( Key == "base" )
					Converter >> CharsetDesc.Base;
				else if( Key == "scaleW" )
					Converter >> CharsetDesc.Width;
				else if( Key == "scaleH" )
					Converter >> CharsetDesc.Height;
				else if( Key == "pages" )
					Converter >> CharsetDesc.Pages;
			}
		}
		else if( Read == "char" )
		{
			//this is data for a specific char
			unsigned short CharID = 0;

			while( !LineStream.eof() )
			{
				std::stringstream Converter;
				LineStream >> Read;
				i = Read.find( '=' );
				Key = Read.substr( 0, i );
				Value = Read.substr( i + 1 );

				Converter << Value;
				if( Key == "id" )
					Converter >> CharID;
				else if( Key == "x" )
					Converter >> CharsetDesc.Chars[CharID].x;
				else if( Key == "y" )
					Converter >> CharsetDesc.Chars[CharID].y;
				else if( Key == "width" )
					Converter >> CharsetDesc.Chars[CharID].Width;
				else if( Key == "height" )
					Converter >> CharsetDesc.Chars[CharID].Height;
				else if( Key == "xoffset" )
					Converter >> CharsetDesc.Chars[CharID].XOffset;
				else if( Key == "yoffset" )
					Converter >> CharsetDesc.Chars[CharID].YOffset;
				else if( Key == "xadvance" )
					Converter >> CharsetDesc.Chars[CharID].XAdvance;
				else if( Key == "page" )
					Converter >> CharsetDesc.Chars[CharID].Page;
			}
		}
	}

	Stream.close();
	return true;
}

TFont::TFont(const std::string& p_strTexture, const std::string& p_strDescription)
{
	ParseFont(p_strDescription, m_Charset);

	m_pTexture = wolf::TextureManager::CreateTexture(p_strTexture);
}

wolf::Texture* TFont::GetTextureForChar(unsigned int p_uiCharId)
{
	// there is only one page char set
	return m_pTexture;
}

void TFont::GetExtentsForChar(const unsigned int p_uiCharId,float *p_uStart,float *p_uEnd,float *p_vStart,float *p_vEnd, 
	unsigned int *p_uiWidth, unsigned int *p_uiHeight, unsigned int *p_uiXAdvance, int *p_uiXOffset, int *p_uiYOffset)
{
	unsigned short width = m_Charset.Width;
	unsigned short height = m_Charset.Height;

	*p_uStart = m_Charset.Chars[p_uiCharId].x / (width*1.0f);
	*p_uEnd = ( m_Charset.Chars[p_uiCharId].x + m_Charset.Chars[p_uiCharId].Width) / (width*1.0f);
	*p_vStart = (height - m_Charset.Chars[p_uiCharId].y) / (height*1.0f);
	*p_vEnd = (height - m_Charset.Chars[p_uiCharId].Height - m_Charset.Chars[p_uiCharId].y) / (height*1.0f);

	*p_uiWidth = m_Charset.Chars[p_uiCharId].Width;
	*p_uiHeight = m_Charset.Chars[p_uiCharId].Height;
	*p_uiXAdvance = m_Charset.Chars[p_uiCharId].XAdvance;
	*p_uiXOffset = m_Charset.Chars[p_uiCharId].XOffset;
	*p_uiYOffset = m_Charset.Chars[p_uiCharId].YOffset;
}

int TFont::GetCharAdvance(unsigned int p_uiCharId)
{
	return m_Charset.Chars[p_uiCharId].XAdvance;
}

int TFont::GetCharHeight(unsigned int p_uiCharId)
{
	return m_Charset.Chars[p_uiCharId].Height;
}