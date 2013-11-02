#pragma once

#include "IScene.h"

// Abstract class for inheriting from

class BasicScene : public IScene
{
protected:
	App* app;

public:
	virtual void Init(App *app);
	virtual void Shutdown();

    virtual void HandleInput(SDL_Event e);
	virtual void Update(double delta) = 0;
	virtual void Render() = 0;

	virtual void Pause();
	virtual void Resume();
    
    
};