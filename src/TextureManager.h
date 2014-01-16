#pragma once

#include <map>
#include <string>

#include "Texture.h"
#include "Font.h"

class TextureManager
{
private:
	std::map<std::string, Texture*> m_Textures;
	std::map<std::string, Font*> m_Fonts;
	SDL_Renderer *m_pRenderer;

public:
	TextureManager();

	bool Init(SDL_Renderer* renderer);
	void Shutdown();

	Texture* GetTexture(std::string filename);
	void LoadTexture(std::string filename);

	Font* GetFont(std::string fntFile);
	void LoadFont(std::string fntFile);

	void SetRenderer(SDL_Renderer *renderer)
	{
		m_pRenderer = renderer;
	}
};