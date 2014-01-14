#include "TextureManager.h"
#include <iostream>
#include <SDL_image.h>

TextureManager::TextureManager()
{
	m_pRenderer = nullptr;
}

bool TextureManager::Init(SDL_Renderer *renderer)
{
	// Initialize SDL_image
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags))	// IMG_Init returns the flags that were successful, so we must and them
	{
		std::cout << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
		return false;
	}

	m_pRenderer = renderer;
	return true;
}

void TextureManager::Shutdown()
{
	// Delete all textures
	if (!m_Textures.empty())
	{
		std::map<std::string, Texture*>::iterator iter;
		for (iter = m_Textures.begin(); iter != m_Textures.end(); m_Textures.erase(iter++)) {
			if (iter->second != nullptr) {
				delete iter->second;
				iter->second = nullptr;
			}
		}
	}
}

void TextureManager::LoadTexture(std::string filename)
{
	if(filename == "") 
		return;

	if (m_pRenderer)
	{
		Texture *texture = new Texture;
		if (!texture || !texture->LoadFile(filename, m_pRenderer))
			return;

		m_Textures[filename] = texture;
	}

	else
		std::cout << "Error loading texture '"  << filename << "': No renderer!" << std::endl;
}

Texture* TextureManager::GetTexture(std::string filename)
{
	if(filename == "") 
		return nullptr;

	if(m_Textures.find(filename) == m_Textures.end()) 
		LoadTexture(filename); 

	return m_Textures[filename];
}