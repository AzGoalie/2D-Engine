#include "App.h"
#include "IScene.h"

#include <iostream>
using std::cout;
using std::endl;

// Declare the global game managers
TextureManager g_TextureManager;


// Initailze static members
App* App::pInstance = nullptr;
IScene* App::pActiveScene = nullptr;

App::App()
{
	// Do nothing except null pointers, everything should be initialized in Init
	m_pWindow = nullptr;
    m_pRenderer = nullptr;
}

App::~App()
{
	// Do nothing, everything should be called in Shutdown()
}

App* App::GetInstance()
{
	if (pInstance == nullptr)
		pInstance = new App();
	return pInstance;
}

void App::Init(const char* title, int width, int height)
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)   // If not 0 then an error occured
	{
        Error("Failed to initialize SDL");
		exit(EXIT_FAILURE);
	}

    // Create our window
    m_pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (!m_pWindow)
	{
		Error("Initialing window failed");
		exit(EXIT_FAILURE);
	}

    // Create our renderer (this is used to draw textures)
    m_pRenderer = SDL_CreateRenderer(m_pWindow, 0, SDL_RENDERER_PRESENTVSYNC);
    if (!m_pRenderer)
    {
        Error("Failed to create renderer");
        exit(EXIT_FAILURE);
    }

	// Initialize the TextureManager
	if (!g_TextureManager.Init(m_pRenderer))
	{
		Error("Failed to initalize the TextureManager");
		exit(EXIT_FAILURE);
	}
}

void App::Shutdown()
{
	// Delete all Scenes
	if (!m_Scenes.empty())
	{
		std::map<std::string, IScene*>::iterator iter;
		for (iter = m_Scenes.begin(); iter != m_Scenes.end(); m_Scenes.erase(iter++)) {
			if (iter->second != nullptr) {
				iter->second->Shutdown();
				delete iter->second;
				iter->second = nullptr;
			}
		}
	}

	pActiveScene = nullptr;

	// Shutdown all the managers
	g_TextureManager.Shutdown();

    // Cleanup on aisle 6
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();

	// Delete the instance
	if (pInstance)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}

void App::Start()
{
	// Timing vars
	int currentTime = GetTime();
	int newTime = 0;
	int delta = 0;

	// Frame timing vars
#ifdef _DEBUG
	int FPS = 0;
	int frames = 0;
	int lastFPSCheck = 0;
#endif
    
    // Quit flag and Event struct
    bool shouldQuit = false;
    SDL_Event e;
    
	while (!shouldQuit)
	{
        // Input polling
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                shouldQuit = true;
                break;
            }
            
            pActiveScene->HandleInput(e);
        }
        
		newTime = GetTime();
		delta = newTime - currentTime;
		currentTime = newTime;

		if (pActiveScene != nullptr)
		{
			pActiveScene->Update(delta);
			pActiveScene->Render();
		}

        // Render the screen
		SDL_RenderPresent(m_pRenderer);

#ifdef _DEBUG
        frames++;
		if (currentTime - lastFPSCheck >= 1000)
		{
			cout << "FPS: " << frames << endl;
			frames = 0;
			lastFPSCheck = currentTime;
		}
#endif
	}
}

void App::AddScene(std::string name, IScene* Scene)
{
	Scene->Init(pInstance);
	m_Scenes[name] = Scene;
	if (pActiveScene == nullptr)
		pActiveScene = Scene;
}

void App::ChangeScene(std::string name)
{
	if (!m_Scenes.empty())
	{
		if (m_Scenes.find(name) != m_Scenes.end())
		{
			if (pActiveScene != nullptr)
				pActiveScene->Pause();
			pActiveScene = m_Scenes.find(name)->second;
			pActiveScene->Resume();
		} 
		
		else 
		{
			cout << "Warrning: No Scene named '" << name << "'" << endl;
		}
	}
}

void App::NextScene()
{
	// TODO: Find a better way to goto the next Scene...
	if (pActiveScene != nullptr)
	{
		std::map<std::string, IScene*>::iterator iter;
		for (iter = m_Scenes.begin(); iter != m_Scenes.end(); ++iter) {
			if (iter->second == pActiveScene)
			{
                iter++;
				pActiveScene->Pause();
				pActiveScene = iter->second;
				pActiveScene->Resume();
				return;
			}
		}

		// If we are here, then it was the last Scene, goto the first
		pActiveScene->Pause();
		pActiveScene = m_Scenes.begin()->second;
		pActiveScene->Resume();
	}
}

void App::Clear()
{
    SDL_RenderClear(m_pRenderer);
}

void App::SetRenderDrawColor(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(m_pRenderer, r, g, b, a);
}

int App::GetTime()
{
	return SDL_GetTicks();
}

void App::Error(std::string msg)
{
    std::cout << "Error: " << msg << std::endl << SDL_GetError() << std::endl;
}
