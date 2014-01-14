#include "TestScene.h"

void TestScene::Init(App *app)
{
	BasicScene::Init(app);
	test = g_TextureManager.GetTexture("data/test.png");
}

void TestScene::Shutdown()
{
}

void TestScene::Update(int delta)
{
}

void TestScene::Render()
{
	app->Clear();
	test->Render(0, 0);
}