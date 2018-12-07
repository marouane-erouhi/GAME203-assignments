#include "Window.h"
#include <SDL.h>
#include <SDL_image.h> //SDL Image component
#include <iostream> /// Umer likes this over printf() - too bad


Window::Window(int width_, int height_){
	screenSurface = nullptr; //Or NULL does the same thing
	window = nullptr;
	width = width_;
	height = height_;
}

bool Window::OnCreate(){
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow("My First Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	//Initialize the SDL_image
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) &imgFlags)) {
		std::cout << "SDL_image could not initialize. SDL_image Error: %s\n" << IMG_GetError() << std::endl;
		return false;
	}

	screenSurface = SDL_GetWindowSurface(window);
	if (screenSurface == nullptr) {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

void Window::OnDestroy(){
	/// Kill the surface first
	if (screenSurface) {
		SDL_FreeSurface(screenSurface);
	}

	/// Now kill the window
	if (window){
		SDL_DestroyWindow(window);
	}

	//Exit SDL Image
	IMG_Quit();
	///Exit the SDL subsystems
	SDL_Quit();

}

Window::~Window(){}

SDL_Window* Window::GetSDL_Window() {
	return window;
}