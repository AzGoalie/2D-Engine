#pragma once

#include "App.h"

// Interface for all scenes

class IScene
{
public:
    virtual ~IScene() {};
	virtual void Init(App *app) = 0;
	virtual void Shutdown() = 0;

	virtual void Update(double delta) = 0;
	virtual void Render() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleInput(SDL_Event e) = 0;
};