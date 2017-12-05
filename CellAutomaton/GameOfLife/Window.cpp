#include "stdafx.h"
#include "Window.h"
#include "SDL_video.h"      // SDL2

namespace Render
{

Window::Window()
{
}

Window::Window(uint32_t width, uint32_t height, std::string title)
{
	Init();
	this->width = width;
	this->height = height;
	this->window = SDL_CreateWindow("SDL_RenderClear", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	this->renderer = SDL_CreateRenderer(this->window, -1, 0);

	if (!(this->window) || !(this->renderer))
	{
		printf("Couldn't create SDL_Window or SDL_Renderer");
	}

	SDL_SetWindowTitle(this->window, title.c_str());
}

Window::~Window()
{

}

void Window::SetBackgroundColor(SDL_Color color)
{
	this->bgColor = color;
	SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
}

void Window::Clear()
{
	SDL_SetRenderDrawColor(this->renderer, this->bgColor.r, this->bgColor.g, this->bgColor.b, this->bgColor.a);
	SDL_RenderClear(this->renderer);
}

void Window::Refresh()
{
	SDL_RenderPresent(this->renderer);
}

void Window::Close()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	this->renderer = nullptr;
	this->window = nullptr;
}

bool Window::Init()
{
	int flags = (SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
	if (SDL_Init(flags) != 0)
	{
		printf("Tried to initialize Video %s", SDL_GetError());
		return false;
	}


	return true;

}

}