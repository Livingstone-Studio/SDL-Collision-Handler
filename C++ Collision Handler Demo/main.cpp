
#include "CollisionHandler.h"

#include "SDL.h"
#include "DemoGameObject.h"
#include <iostream>

using namespace std;

void Test1() 
{
	cout << "C1" << endl;
}

void Test2() 
{
	cout << "C2" << endl;
}

bool InputEvents() 
{
	// Local declaration of an sdl event.
	SDL_Event m_event;

	// Loops until all input events are handled.
	while (SDL_PollEvent(&m_event))
	{
		// Checks if the event type is the 'X' button in the top right of the window, if so - return false.
		switch (m_event.type)
		{
		case SDL_QUIT:
			return true;
			break;
		}
	}

}

int main(int argc, char* argv[])
{
	// SDL initialization.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		// Error
		cout << "Failed to intialise SDL. Error: " << SDL_GetError() << endl;
	}
	
	// Window and renderer creation.
	SDL_Window* window = SDL_CreateWindow("Collision Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 580, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	std::vector<DemoGameObject*> demo_gos;

	demo_gos.push_back(new DemoGameObject({ 200,120,100,100 }, 1, 1, new SquareCollider(200, 120, 100, 100, Test1)));
	demo_gos.push_back(new DemoGameObject({ 700,500,100,100 }, -1, -1, new SquareCollider(700, 500, 100, 100, Test2)));

	// COLLISION USAGE -- START

	// Add 

	for (DemoGameObject* go : demo_gos)
	{
		if (go)
		{
			CollisionHandler::Add(go->GetCollider());
			
		}
	}

	while (true) 
	{
		if (InputEvents()) break; // NOT APART OF COLLISION SYSTEM - JUST SIMPLE INPUT HANDLING

		SDL_RenderClear(renderer);

		for (DemoGameObject* go : demo_gos)
		{
			if (go)
			{
				go->Move();
				go->Draw(renderer);
			}
		}

		CollisionHandler::Update();

		SDL_RenderPresent(renderer);
		SDL_Delay(50);
	}

	CollisionHandler::Cleanup();

	// COLLISION USAGE -- END

	// Window cleanup.
	SDL_DestroyWindow(window);

	window = nullptr;

	// Renderer cleanup.
	SDL_DestroyRenderer(renderer);

	renderer = nullptr;

	// SDL cleanup.
	SDL_Quit();

	return 0;
}