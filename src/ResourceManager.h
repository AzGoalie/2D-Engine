#pragma once

#include <map>
#include <string>

#include "Texture.h"
#include "Font.h"

class ResourceManager
{
private:
	std::map<std::string, Texture*> m_Textures;
	std::map<std::string, Font*> m_Fonts;
	SDL_Renderer *m_pRenderer;
    
    char* BASE_PATH;    // Base path of the application

public:
	ResourceManager();

	bool Init(SDL_Renderer* renderer);
	void Shutdown();

	Texture* GetTexture(std::string filename);
	void LoadTexture(std::string filename);

	Font* GetFont(std::string fntFile);
	void LoadFont(std::string fntFile);
    
    std::string GetBasePath() { return BASE_PATH; }

	void SetRenderer(SDL_Renderer *renderer)
	{
		m_pRenderer = renderer;
	}
};