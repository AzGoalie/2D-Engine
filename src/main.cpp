#include <iostream>

#include "App.h"
#include "TestScene.h"

int main()
{
    // Get our app/game
	App* app = App::GetInstance();

    // Initialize our app
	app->Init("Test", 640, 480, 3, 2);
    
    // Add scenes here
	app->AddScene("TestScene1", new TestScene);
	
    // Start
    app->Start();

    // When finished, cleanup
	app->Shutdown();
	return 0;
}