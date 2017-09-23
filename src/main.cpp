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
SDL_Event e;
bool quit = false;

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
	int posX, posY, width, height;
	posX = posY = 0;
	//posX = gHelloWorld->w;
	width = gHelloWorld->clip_rect.w;
	height = gHelloWorld->clip_rect.h;
	while (!quit)
	{
		// Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			// Check if user requested quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_UP:
				{
					posY--;
					break;
				}

				case SDLK_DOWN:
				{
					posY++;
					break;
				}

				case SDLK_LEFT:
				{
					posX--;
					break;
				}

				case SDLK_RIGHT:
				{
					posX++;
					break;
				}
				
				default:
				{
					break;
				}

				}
			}

			

		}

		SDL_Rect tmp = { posX, posY, width, height };
		// Apply the image
		SDL_FillRect(gScreenSurface, NULL, 0x000000);
		SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, &tmp);
		// Update the surface
		SDL_UpdateWindowSurface(gWindow);		
	}

	LOG_INFO("End session");

	return 0;
}