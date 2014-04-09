#pragma once

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include <SDL.h>
#endif

#include <map>
#include <string>
#include "ResourceManager.h"

class IScene;

// Global game managers
extern ResourceManager g_ResourceManager;

class App
{
private:
    
	// Singleton instance
	static App* pInstance;
	static IScene* pActiveScene;

private:
	SDL_Window* m_pWindow;                      // The actual window
    SDL_Renderer *m_pRenderer;                  // Drawing context
	std::map<std::string, IScene*> m_Scenes;    // List of scenes
    
public:
	static App* GetInstance();  // Singleton access
	~App();

	void Init(const char* title, int width, int height);
	void Shutdown();

	void Start();

	void AddScene(std::string name, IScene* Scene);
	void ChangeScene(std::string name);	// Goto a specific Scene
    void NextScene();					// Goes to the next Scene in the map
	IScene* GetCurrentScene() { return pActiveScene; }

    void Clear();
    void SetRenderDrawColor(int r, int g, int b, int a);
    
    SDL_Window* GetWindow() { return m_pWindow; }
    SDL_Renderer* GetRenderer() { return m_pRenderer; }
    
    // Returns the number of miliseconds since app start
	int GetTime();

	void Quit();

    // Print out an error message
    void Error(std::string msg);

    
private:
	App();
};