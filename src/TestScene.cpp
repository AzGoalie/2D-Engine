#include "TestScene.h"

void TestScene::Init(App *app)
{
	BasicScene::Init(app);
    app->SetRenderDrawColor(255, 0, 0, 255);
}

void TestScene::Shutdown()
{
    
}

void TestScene::Update(double delta)
{

}

void TestScene::Render()
{
    app->Clear();
}