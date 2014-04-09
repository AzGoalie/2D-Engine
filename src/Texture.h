#pragma once

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include <SDL.h>
#endif

#include <string>

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

	bool LoadFile(std::string filename, SDL_Renderer* renderer);
	void Render(int x, int y, SDL_Rect* clip = NULL);
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
};