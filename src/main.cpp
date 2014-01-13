#include <iostream>

#include "App.h"
#include "TestScene.h"

// Memory leak checks
#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

int main(int argc, char *argv[])
{
    // Get our app/game
	App* app = App::GetInstance();

    // Initialize our app
	app->Init("Test", 640, 480);
    
    // Add scenes here
	app->AddScene("TestScene1", new TestScene);
	
    // Start
    app->Start();

    // When finished, cleanup
	app->Shutdown();

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}