#include "FontTest.h"

void FontTest::Init(App *app)
{
	BasicScene::Init(app);
	font = g_ResourceManager.GetFont("data/fonts/arial.fnt");
}

void FontTest::Shutdown()
{
}

void FontTest::Update(int delta)
{
}

void FontTest::Render()
{
	app->Clear();
	font->Render(0, 0, "abcdefghijklmnopqrstuvwxyz");
	font->Render(0, 25, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	font->Render(0, 50, "1234567890");
	font->Render(0, 75, "~!@#$%^&*()_+-=/\\><.,");
	font->Render(0, 100, 65532);	// Obj symbol
    font->Render(0, 125, "The quick brown fox jumped over the lazy dog");
}