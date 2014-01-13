#include "TestScene.h"

void TestScene::Init(App *app)
{
	BasicScene::Init(app);
	test.LoadFile("data/test.png", app->GetRenderer());
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
	test.Render(0, 0);
}