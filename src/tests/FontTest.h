#pragma once

#include "BasicScene.h"
#include "Font.h"

// Simple test for fonts

class FontTest : public BasicScene
{
private:
	Font *font;
    
public:
    
	void Init(App *app);
	void Shutdown();
    
	void Update(int delta);
	void Render();
};