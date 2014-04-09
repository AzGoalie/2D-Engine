#include "ResourceManager.h"
#include <iostream>

#ifdef __APPLE__
    #include <SDL2_image/SDL_image.h>
#else
    #include <SDL_image.h>
#endif

ResourceManager::ResourceManager()
{
	m_pRenderer = nullptr;
}

bool ResourceManager::Init(SDL_Renderer *renderer)
{
	// Initialize SDL_image
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags))	// IMG_Init returns the flags that were successful, so we must and them
	{
		std::cout << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
		return false;
	}

    // Find the base path
    BASE_PATH = SDL_GetBasePath();
    if (!BASE_PATH)
    {
        std::cout << "Failed to find base path" << std::endl;
        return false;
    }
    
	m_pRenderer = renderer;
	return true;
}

void ResourceManager::Shutdown()
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

	// Delete all fonts
	if (!m_Fonts.empty())
	{
		std::map<std::string, Font*>::iterator iter;
		for (iter = m_Fonts.begin(); iter != m_Fonts.end(); m_Fonts.erase(iter++)) {
			if (iter->second != nullptr) {
				delete iter->second;
				iter->second = nullptr;
			}
		}
	}
    
    // Delete base path
    SDL_free(BASE_PATH);
}

void ResourceManager::LoadTexture(std::string filename)
{
	if(filename == "") 
		return;

	if (m_pRenderer)
	{
		Texture *texture = new Texture;
		texture->LoadFile(filename, m_pRenderer);	// TODO: do something if it fails
		m_Textures[filename] = texture;
	}

	else
		std::cout << "Error loading texture '"  << filename << "': No renderer!" << std::endl;
}

Texture* ResourceManager::GetTexture(std::string filename)
{
	if(filename == "") 
		return nullptr;

	if(m_Textures.find(filename) == m_Textures.end()) 
		LoadTexture(filename); 

	return m_Textures[filename];
}

void ResourceManager::LoadFont(std::string fntFile)
{
	if (fntFile == "")
		return;
    
	if (m_pRenderer)
	{
		Font *font = new Font;
		font->LoadFont(BASE_PATH + fntFile, m_pRenderer);
		m_Fonts[fntFile] = font;
	}

	else
		std::cout << "Error loading font '"  << fntFile << "': No renderer!" << std::endl;
}

Font* ResourceManager::GetFont(std::string fntFile)
{
	if(fntFile == "") 
		return nullptr;

	if(m_Fonts.find(fntFile) == m_Fonts.end()) 
		LoadFont(fntFile); 

	return m_Fonts[fntFile];
}