#include "Texture.h"
#include <SDL_image.h>

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

bool Texture::LoadFile(const char* filename, SDL_Renderer* renderer)
{
	// Check to make sure we're not already bound
	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	m_pTexture = IMG_LoadTexture(renderer, filename);
	if (!m_pTexture)
		return false;

	// Get width and height
	SDL_QueryTexture(m_pTexture, NULL, NULL, &m_Width, &m_Height);

	m_pRenderer = renderer;
	return true;
}

void Texture::Render(int x, int y, SDL_Rect* clip)
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