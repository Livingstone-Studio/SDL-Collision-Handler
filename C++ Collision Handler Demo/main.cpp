
#include "CollisionHandler.h"

#include "SDL.h"
#include "DemoGameObject.h"
#include <iostream>

using namespace std;

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

	// COLLISION USAGE -- START
	
	// Horizontal Walls
	demo_gos.push_back(new DemoGameObject({ 490, 0, 1000, 100 }, 0, 0, Collider::RECT));
	demo_gos.push_back(new DemoGameObject({ 490, 580, 1000,100 }, 0, 0, Collider::RECT));

	// Vertical Walls
	demo_gos.push_back(new DemoGameObject({ 0, 290,100,700 }, 0, 0, Collider::RECT));
	demo_gos.push_back(new DemoGameObject({ 960, 290, 100,700 }, 0, 0, Collider::RECT));
	
	// Moving
	demo_gos.push_back(new DemoGameObject({ 700, 290, 25, 100 }, -1, 0, Collider::RECT));
	demo_gos.push_back(new DemoGameObject({ 200,290,100,100 }, 1, 0, Collider::CIRCLE));

	demo_gos.push_back(new DemoGameObject({ 200,100,50,50 }, 0, 1, Collider::RECT));
	demo_gos.push_back(new DemoGameObject({ 700,100,50,100 }, 0, 1, Collider::CIRCLE));

	while (true) 
	{
		if (InputEvents()) break;

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
		SDL_Delay(5);
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