#include "Texture.h"
#include <SDL2_image/SDL_image.h>
#include <iostream>

Texture::Texture()
{
	m_pTexture = nullptr;
	m_pRenderer = nullptr;
	m_Width = 0;
	m_Height = 0;
}

Texture::~Texture()
{
	if (m_pTexture)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = nullptr;
	}

	// The renderer will be deleted by the App class
	m_pRenderer = nullptr;

	m_Width = 0;
	m_Height = 0;
}

bool Texture::LoadFile(std::string filename, SDL_Renderer* renderer)
{
	// Check to make sure we're not already bound
	if (m_pTexture)
	{
        	SDL_DestroyTexture(m_pTexture);
		m_pTexture = nullptr;
	}

	m_pTexture = IMG_LoadTexture(renderer, filename.c_str());
	if (!m_pTexture)
	{
		std::cout << "Error loading image '" << filename << "': " << IMG_GetError() << std::endl;
		return false;
	}

	// Get width and height
	SDL_QueryTexture(m_pTexture, NULL, NULL, &m_Width, &m_Height);

	m_pRenderer = renderer;
	return true;
}

void Texture::Render(int x, int y, SDL_Rect* clip)
{
	if (m_pTexture)
	{
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		rect.w = m_Width;
		rect.h = m_Height;

		if (clip)
		{
			rect.w = clip->w;
			rect.h = clip->h;
		}

		SDL_RenderCopy(m_pRenderer, m_pTexture, clip, &rect);
	}
}

void Texture::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	if (m_pTexture)
	{
		SDL_SetTextureColorMod(m_pTexture, r, g, b);
	}
}
