#include "stdafx.h"
#include "application.h"
#include <ctime>
#include "SDL_image.h"

//#define READ_TEXTURE
#define RANDOM

namespace App
{

Application::Application()
{
}

Application::Application(std::shared_ptr<Render::Window> window)
{
	this->window = window;
	this->rend = this->window->GetRenderer();
}

Application::~Application()
{

}

bool Application::Open()
{
#ifdef RANDOM
	width = window->GetWidth() / QUAD_SIZE;
	height = window->GetHeight() / QUAD_SIZE;

	srand(time(0));

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			cells.push_back(Cell(x*QUAD_SIZE, y*QUAD_SIZE, width, height, rend, (rand()%100)%2));
		}
	}

#endif

#ifdef READ_TEXTURE
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF; 
	if (!(IMG_Init(imgFlags) & imgFlags)) 
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}

	// get the surface and the bits per pixel
	SDL_Surface * surface = IMG_Load("test.tif");
	width = surface->w;
	height = surface->h;
	SDL_LockSurface(surface);
	unsigned char* pixels = static_cast<unsigned char*>(surface->pixels);

	//Uint8* p = static_cast<Uint8*>(surface->pixels);

	
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			cells.push_back(Cell(x*QUAD_SIZE, y*QUAD_SIZE, width, height, rend, pixels[4 * (y * surface->w + x) + 0]));
		}
	}

	SDL_UnlockSurface(surface);
#endif
	updatedCells = cells;
	state = Paused;

	return true;
}

void Application::Run()
{
	Uint32 last = 0, timeElapsed = 0;
	while (this->window->IsOpen())
	{
		this->window->Clear();
		Events();
		HandleKeys();
		uint32_t now = SDL_GetTicks();
		timeElapsed = now - last;

		if (timeElapsed >= UPDATEINTERVAL)
		{
			last = now;
			Update();
		}
		
		this->window->Refresh();
	}
	
}

void Application::Update()
{
	if (state == Simulating)
	{
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				CheckNeighbours(x, y);
			}
		}
		cells = updatedCells;
	}

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{

			cells[y*width + x].Draw();
		}
	}
	
}

void Application::Events()
{
	if (SDL_PollEvent(&this->event))
	{
		switch (this->event.type)
		{
		case SDL_QUIT:  this->window->Close();  break;
		case SDL_KEYDOWN: OnKeyDown(&this->event);  break;
		case SDL_KEYUP: OnKeyUp(&this->event);  break;
		case SDL_MOUSEBUTTONDOWN: break;
		case SDL_MOUSEBUTTONUP: break;
		case SDL_MOUSEMOTION: break;
		case SDLK_SPACE: state = Simulating; break;
		case SDLK_p: state = Paused; break;
		default: break;
		}
	}
}

void Application::CheckNeighbours(const int& x, const int& y)
{
	unsigned c = 0;

	for (int nY = -1; nY <= 1; ++nY)
	{
		for (int nX = -1; nX <= 1; ++nX)
		{
			int newX = nX + x;
			int newY = nY + y;

			if (newX == -1 || newX == width || newY == -1 || newY == height || (nX == 0 && nY == 0))
				continue;

			if (cells[newY*width+newX].GetAlive())
				c++;

		}
	}

	auto cell = cells[y*width + x];
	auto& uCell = updatedCells[y*width + x];

	if (cell.GetAlive())
	{
		if (c < 2 || c > 3)
		{
			uCell.SetLife(false);
		}
	}
	else
	{
		if (c == 3)
		{
			uCell.SetLife(true);
		}
	}
}

void Application::OnKeyDown(SDL_Event* e)
{
	this->userKeys[this->event.key.keysym.sym] = 1;
}

void Application::OnKeyUp(SDL_Event* e)
{
	this->userKeys[this->event.key.keysym.sym] = 0;
}

void Application::HandleKeys()
{
	if (userKeys[SDLK_SPACE])
	{
		state = Simulating;
	}
	else if (userKeys[SDLK_p])
	{
		state = Paused;
	}
}
}

