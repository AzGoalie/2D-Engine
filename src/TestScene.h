#pragma once

#include "BasicScene.h"
#include "Texture.h"
#include "Font.h"

// Simple example scene to show how to use the framework

class TestScene : public BasicScene
{
private:
	Texture *test;
	Font font;

public:
    
	void Init(App *app);
	void Shutdown();

	void Update(int delta);
	void Render();
};