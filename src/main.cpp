#include <SDL.h>
#include <SDL_Image.h>
#include <stdio.h>

#include "Utils/Logger.h"

const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

bool Init();
bool LoadMedia();
void Close();
SDL_Surface* LoadSurface(std::string path);

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

	// Load SDL2 Image extension
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	int result = IMG_Init(imgFlags);
	if ((result & imgFlags) != imgFlags) 
	{
		LOG_ERROR("SDL_image could not be initialized! SDL_image error: %s\n", IMG_GetError());
		return false;
	}

	gScreenSurface = SDL_GetWindowSurface(gWindow);

	return true;
}

bool LoadMedia()
{
	//gHelloWorld = LoadSurface("data/flower.bmp");
	gHelloWorld = LoadSurface("data/egg.jpg");
	if (!gHelloWorld)
	{
		LOG_ERROR("Could not load media! SDL error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

SDL_Surface* LoadSurface(std::string path)
{
	SDL_Surface* optimizedSurface = nullptr;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		LOG_ERROR("Unable to load image %s! SDL_image error: %s", path.c_str(), IMG_GetError());
		return nullptr;
	}


	optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
	if (optimizedSurface == nullptr)
	{
		LOG_ERROR("Unable to optimize image %s! SDL error: %s", path.c_str(), SDL_GetError());
	}
	
	// SDL_ConvertSurface will return a new copy of the original surface,
	// so must free the original surface in any case of converting.
	SDL_FreeSurface(loadedSurface);

	return optimizedSurface;
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
	
	width = gHelloWorld->clip_rect.w;
	height = gHelloWorld->clip_rect.h;
	posX = (SCREEN_WIDTH - width) / 2;
	posY = (SCREEN_HEIGHT - height) / 2;

	SDL_Rect stretchedRect = { 0, 0, width/4, height/4 };

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
		SDL_BlitScaled(gHelloWorld, NULL, gScreenSurface, &stretchedRect);
		SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, &tmp);
		
		// Update the surface
		SDL_UpdateWindowSurface(gWindow);		
	}

	LOG_INFO("End session");

	return 0;
}