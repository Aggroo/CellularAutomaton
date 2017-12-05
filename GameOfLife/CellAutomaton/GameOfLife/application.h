#pragma once
#include "SDL.h"
#include <string>
#include "Window.h"
#include <memory>
#include <vector>
#include "Cell.h"
#include <map>

#define UPDATEINTERVAL 1.66
#define QUAD_SIZE 4

namespace App
{
enum State
{
	Simulating,
	Paused
};

class Application
{
public:

	Application();
	Application(std::shared_ptr<Render::Window> window);
	~Application();

	bool Open();
	void Run();

	void Update();

	//Key events. Listens to Key Down, Key Up and mouse clicks
	void Events();

	void CheckNeighbours(const int& x, const int& y);

	//Called from Events when a key is pressed down
	void OnKeyDown(SDL_Event* e);

	//Called from Events when a key is released
	void OnKeyUp(SDL_Event* e);

	void HandleKeys();

private:

	//Smart pointer of the Window object
	std::shared_ptr<Render::Window> window;

	//The cells that is drawn and checked
	std::vector<Cell> cells;
	//The temporary cells that is updated during each check
	std::vector<Cell> updatedCells;

	int width, height;

	State state;

	//Map to keep track of what keys have been pressed
	std::map<SDL_Keycode, int> userKeys;

	////////////////////////////
	///SDL specific variables///
	SDL_Renderer *rend;
	SDL_Event event;
	////////////////////////////

};

}


