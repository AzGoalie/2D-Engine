#pragma once

#include <SDL.h>

class Texture
{
private:
	SDL_Texture *m_pTexture;
	SDL_Renderer *m_pRenderer;
	int m_Width;
	int m_Height;

public:
	Texture();
	~Texture();

	bool LoadFile(const char* filename, SDL_Renderer* renderer);
	void Render(int x, int y, SDL_Rect* clip = NULL);
};