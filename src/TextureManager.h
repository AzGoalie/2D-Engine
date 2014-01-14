#pragma once

#include <map>
#include <string>

#include "Texture.h"

class TextureManager
{
private:
	std::map<std::string, Texture*> m_Textures;
	SDL_Renderer *m_pRenderer;

public:
	TextureManager();

	bool Init(SDL_Renderer* renderer);
	void Shutdown();

	Texture* GetTexture(std::string filename);
	void LoadTexture(std::string filename);

	void SetRenderer(SDL_Renderer *renderer)
	{
		m_pRenderer = renderer;
	}
};