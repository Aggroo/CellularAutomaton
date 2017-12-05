#include "stdafx.h"
#include "Cell.h"

Cell::Cell(int x, int y, int width, int height, SDL_Renderer* renderer, unsigned char c)
{
	this->width = width;
	this->height = height;

	this->renderer = renderer;


	this->cell.x = x;
	this->cell.y = y;
	this->cell.w = 1 + width;
	this->cell.h = 1 + height;

	liveCol = { 0, 0, 0, 255 };
	deadCol = { 255, 255, 255, 255 };

	if ((int) c < 255)
	{
		this->alive = true;
		currentCol = liveCol;
	}
	else
	{
		this->alive = false;
		currentCol = deadCol;
	}
	
}

Cell::Cell(int x, int y, int width, int height, SDL_Renderer* renderer, int alive)
{
	this->width = width;
	this->height = height;

	this->renderer = renderer;


	this->cell.x = x;
	this->cell.y = y;
	this->cell.w = 1 + width;
	this->cell.h = 1 + height;

	liveCol = { 0, 0, 0, 255 };
	deadCol = { 255, 255, 255, 255 };

	if (alive == 1)
	{
		this->alive = true;
		currentCol = liveCol;
	}
	else
	{
		this->alive = false;
		currentCol = deadCol;
	}
}


Cell::~Cell()
{
}

void Cell::Draw()
{
	SDL_SetRenderDrawColor(this->renderer, currentCol.r, currentCol.g, currentCol.b, currentCol.a);
	SDL_RenderFillRect(this->renderer, &this->cell);
}

void Cell::SetLife(bool alive)
{
	this->alive = alive;

	if (this->alive)
		currentCol = liveCol;
	else
		currentCol = deadCol;
}

bool Cell::GetAlive()
{
	return alive;
}
