#pragma once
#include <SDL.h>
#include <vector>

class Cell
{
public:

	Cell(int x, int y, int width, int height, SDL_Renderer* renderer, unsigned char c);
	Cell(int x, int y, int width, int height, SDL_Renderer* renderer, int alive);
	~Cell();

	void Draw();

	void SetLife(bool alive);
	bool GetAlive();

private:
	bool alive;

	int width, height;

	SDL_Rect cell;

	SDL_Renderer* renderer;

	SDL_Color currentCol;

	SDL_Color liveCol;
	SDL_Color deadCol;

	
};

