// GameOfLife.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Window.h"
#include <memory>
#include "application.h"

int main(int argc, char **argv)
{
	std::shared_ptr<Render::Window> window = std::make_shared<Render::Window>(1024, 720, "A Game of Life");
	SDL_Color c;
	c.r = 0;
	c.g = 255;
	c.b = 0;
	c.a = 255;
	window->SetBackgroundColor(c);

	//Create the Game logics
	App::Application app(window);
	app.Open();
	//Run the main function of the Game logics.
	app.Run();

	SDL_Quit();

	return 0;
}

