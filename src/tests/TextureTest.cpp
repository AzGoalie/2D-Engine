#include "TextureTest.h"

void TextureTest::Init(App *app)
{
	BasicScene::Init(app);
	texture1 = g_ResourceManager.GetTexture("data/tests/test.png");
    texture2 = g_ResourceManager.GetTexture("data/tests/img_test.png");
    
}

void TextureTest::Shutdown()
{
}

void TextureTest::Update(int delta)
{
}

void TextureTest::Render()
{
	app->Clear();
	texture1->Render(0, 0);
    texture2->Render(0, 0);
}