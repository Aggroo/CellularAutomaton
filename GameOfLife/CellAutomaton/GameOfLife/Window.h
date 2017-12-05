#pragma once
#include <SDL.h>
#include <string>

namespace Render
{
	
//Window class. Used to easy set up a window
class Window
{
public:
	Window();

	//Sets up all the necessary components
	Window(uint32_t width, uint32_t height, std::string title);
	~Window();

	//Sets a background color for SDL
	void SetBackgroundColor(SDL_Color color);
	//Clears the renderer
	void Clear();
	//Returns true as long as this is not a nullptr
	const bool IsOpen() const;
	//Renders the present setup 
	void Refresh();

	//Getters
	uint32_t& GetWidth(){ return width; }
	uint32_t& GetHeight(){ return height; }
	SDL_Renderer* GetRenderer(){ return renderer; }

	//Cleans up and closes the window
	void Close();

private:
	//Initializes SDL2
	bool Init();

	//width and height of the window
	uint32_t width;
	uint32_t height;

	// SDL's internal data structure that represents the window.
	SDL_Window* window;

	// SDL's internal data structure that represents the renderer. Contained by the window
	SDL_Renderer* renderer;

	//Background color
	SDL_Color bgColor;


};

inline const bool Window::IsOpen() const
{
	return nullptr != this->window;
}

}


