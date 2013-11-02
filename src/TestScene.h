#pragma once

#include "BasicScene.h"

// Simple example scene to show how to use the framework

class TestScene : public BasicScene
{
private:
public:
    
	void Init(App *app);
	void Shutdown();

	void Update(double delta);
	void Render();
};