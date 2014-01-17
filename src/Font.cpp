#include "Font.h"

#include <fstream>
#include <sstream>

using namespace std;

Font::Font()
{
	m_pBitmap = nullptr;
}

Font::~Font()
{
	if (m_pBitmap)
	{
		delete m_pBitmap;
		m_pBitmap = nullptr;
	}
}

bool Font::LoadFont(string fntFile, SDL_Renderer *renderer)
{
	string line;
	string read, key, value;
	size_t i;

	// Load the .fnt file
	ifstream fnt(fntFile);
	if (fnt.is_open())
	{
		// Parse the .fnt file
		while(!fnt.eof())
		{
			stringstream lineStream;
			getline(fnt, line);
			lineStream << line;

			// read the line's type
			lineStream >> read;
			if (read == "common")
			{
				while (!lineStream.eof())
				{
					stringstream converter;
					lineStream >> read;
					i = read.find('=');
					key = read.substr(0, i);
					value = read.substr(i+1);

					// assign th correct value
					converter << value;
					if (key == "lineHeight")
						converter >> m_Charset.lineHeight;
					else if (key == "base")
						converter >> m_Charset.base;
					else if (key == "scaleW")
						converter >> m_Charset.width;
					else if (key == "scaleH")
						converter >> m_Charset.height;
					else if (key == "pages")
						converter >> m_Charset.pages;
				}
			}

			// Use this to load the proper font image
			else if (read == "page")
			{
				string filename;
				while (!lineStream.eof())
				{
					stringstream converter;
					lineStream >> read;
					i = read.find('=');
					key = read.substr(0, i);
					value = read.substr(i+1);

					// assign th correct value
					converter << value;
					if (key == "file")
					{
						converter >> filename;
						// Remove quotation marks around filename
						filename = filename.substr(1, filename.size()-2);
						filename = "data/fonts/" + filename;	// TODO: remove hard coded value
					}
				}

				if (!filename.empty())
				{
					m_pBitmap = new Texture;
					if (!m_pBitmap->LoadFile(filename, renderer))
						return false;
				}
			}

			else if (read == "char")
			{
				unsigned short charID = 0;

				while (!lineStream.eof())
				{
					stringstream converter;
					lineStream >> read;
					i = read.find('=');
					key = read.substr(0, i);
					value = read.substr(i + 1);

					// assign the correct value
					converter << value;
					if (key == "id")
						converter >> charID;
					else if (key == "x")
						converter >> m_Charset.chars[charID].x;
					else if (key == "y")
						converter >> m_Charset.chars[charID].y;
					else if (key == "width")
						converter >> m_Charset.chars[charID].width;
					else if (key == "height")
						converter >> m_Charset.chars[charID].height;
					else if (key == "xoffset")
						converter >> m_Charset.chars[charID].xOffset;
					else if (key == "yoffset")
						converter >> m_Charset.chars[charID].yOffset;
					else if (key == "xadvance")
						converter >> m_Charset.chars[charID].xAdvance;
					else if (key == "page")
						converter >> m_Charset.chars[charID].page;
				}
			}
		}

		fnt.close();
		return true;
	}
	else
		return false;
}

void Font::Render(int x, int y, string text)
{
	if (m_pBitmap)
	{
		SDL_Rect src;
		int cursorX = x;
		for (unsigned int i = 0; i < text.size(); i++)
		{
			int cursorY = y;
			src.x = m_Charset.chars[text[i]].x;
			src.y = m_Charset.chars[text[i]].y;
			src.w = m_Charset.chars[text[i]].width;
			src.h = m_Charset.chars[text[i]].height;

			cursorX += m_Charset.chars[text[i]].xOffset;
			cursorY += m_Charset.chars[text[i]].yOffset;


			m_pBitmap->Render(cursorX, cursorY, &src);
			cursorX += m_Charset.chars[text[i]].xAdvance;
		}
	}
}

void Font::Render(int x, int y, unsigned short c)
{
	if (m_pBitmap)
	{
		SDL_Rect src;
		int cursorX = x;
		int cursorY = y;

		src.x = m_Charset.chars[c].x;
		src.y = m_Charset.chars[c].y;
		src.w = m_Charset.chars[c].width;
		src.h = m_Charset.chars[c].height;

		cursorX += m_Charset.chars[c].xOffset;
		cursorY += m_Charset.chars[c].yOffset;


		m_pBitmap->Render(cursorX, cursorY, &src);
	}
}
