#pragma once

#include <map>
#include <string>

#include "Texture.h"

struct CharDescriptor
{
	unsigned short x, y;
	unsigned short width, height;
	short xOffset;
	unsigned short yOffset;
	unsigned short xAdvance;
	unsigned short page;

	CharDescriptor() : x(0), y(0), width(0), height(0), 
		xOffset(0), yOffset(0), xAdvance(0), page(0)
	{}
};

struct Charset
{
	unsigned short lineHeight;
	unsigned short base;
	unsigned short width, height;
	unsigned short pages;
	std::map<unsigned short, CharDescriptor> chars;
};

class Font
{
private:
	Charset m_Charset;

public:
	Texture *m_pBitmap;
	Font();
	~Font();

	// .fnt file and Renderer to load the texture
	bool LoadFont(std::string fntFile, SDL_Renderer *renderer);
	void Render(int x, int y, std::string text);
	void Render(int x, int y, unsigned short c);
};