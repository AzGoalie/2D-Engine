#include "TestScene.h"

void TestScene::Init(App *app)
{
	BasicScene::Init(app);
	test = g_TextureManager.GetTexture("data/test.png");
	font.LoadFont("data/fonts/arial.fnt", app->GetRenderer());
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
	font.Render(0, 0, "abcdefghijklmnopqrstuvwxyz");
	font.Render(0, 20, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	font.Render(0, 40, "1234567890");
	font.Render(0, 60, "~!@#$%^&*()_+-=/\><.,");
	font.Render(100, 100, 65532);	// Obj symbol
}