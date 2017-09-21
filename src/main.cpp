#include <SDL.h>
#include <stdio.h>

#include "Utils/Logger.h"

const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;


int main(int argc, char* args[])
{
	LOG_INFO("Start session");

	SDL_Window *window = nullptr;
	SDL_Surface *screenSurface = nullptr;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG_ERROR("SDL could not be initialized! SDL error: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("SDL2 Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
	{
		LOG_ERROR("Window could not be created! SDL error: %s\n", SDL_GetError());
		return 1;
	}

	screenSurface = SDL_GetWindowSurface(window);

	// Fill the surface white
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

	// Update the surface
	SDL_UpdateWindowSurface(window);

	// Wait 2 seconds before exiting
	SDL_Delay(2000);

	// Destroy window
	SDL_DestroyWindow(window);

	// Quit SDL subsystems
	SDL_Quit();	

	LOG_INFO("End session");

	return 0;
}