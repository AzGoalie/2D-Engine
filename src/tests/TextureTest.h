#pragma once

#include "../BasicScene.h"
#include "../Texture.h"

// Simple test for textures

class TextureTest : public BasicScene
{
private:
	Texture *texture1;
    Texture *texture2;
    
public:
    
	void Init(App *app);
	void Shutdown();
    
	void Update(int delta);
	void Render();
};