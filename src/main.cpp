#include <SDL.h>
#include <stdio.h>

#include "Utils/Logger.h"

const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

bool Init();
bool LoadMedia();
void Close();

SDL_Window *gWindow = nullptr;
SDL_Surface *gScreenSurface = nullptr;
SDL_Surface *gHelloWorld = nullptr;

bool Init()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG_ERROR("SDL could not be initialized! SDL error: %s\n", SDL_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("SDL2 Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!gWindow)
	{
		LOG_ERROR("Window could not be created! SDL error: %s\n", SDL_GetError());
		return false;
	}

	gScreenSurface = SDL_GetWindowSurface(gWindow);

	return true;
}

bool LoadMedia()
{
	gHelloWorld = SDL_LoadBMP("data/flower.bmp");
	if (!gHelloWorld)
	{
		LOG_ERROR("Could not load media! SDL error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

void Close()
{
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	SDL_Quit();
}

int main(int argc, char* args[])
{
	LOG_INFO("Start session");

	if (!Init())
	{
		return false;
	}

	if (!LoadMedia())
	{
		return false;
	}

	// Apply the image
	SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
	// Update the surface
	SDL_UpdateWindowSurface(gWindow);

	// Wait 2 seconds before exiting
	SDL_Delay(2000);
	
	LOG_INFO("End session");

	return 0;
}