#include "stdafx.h"

#include "Texture.h"

const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;

bool Init();
bool LoadMedia();
void Close();
SDL_Texture* LoadTexture(std::string path);
void DrawPrimitives();

SDL_Window *gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
Texture gTexture1;
Texture gTexture2;
SDL_Rect gSpriteClips[4];
Texture gSpriteSheetTexture;
SDL_Event e;
bool quit = false;



bool Init()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG_ERROR("SDL could not be initialized! SDL error: %s", SDL_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("SDL2 Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!gWindow)
	{
		LOG_ERROR("Window could not be created! SDL error: %s", SDL_GetError());
		return false;
	}	
	
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!gRenderer)
	{
		LOG_ERROR("Renderer could not be created! SDL error: %s", SDL_GetError());
		return false;
	}

	// Initialize renderer color
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// Initialize SDL2 Image extension
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	int result = IMG_Init(imgFlags);
	if ((result & imgFlags) != imgFlags) 
	{
		LOG_ERROR("SDL_image could not be initialized! SDL_image error: %s", IMG_GetError());
		return false;
	}

	//Set top left sprite
	gSpriteClips[0].x = 0;
	gSpriteClips[0].y = 0;
	gSpriteClips[0].w = 100;
	gSpriteClips[0].h = 100;

	//Set top right sprite
	gSpriteClips[1].x = 100;
	gSpriteClips[1].y = 0;
	gSpriteClips[1].w = 100;
	gSpriteClips[1].h = 100;

	//Set bottom left sprite
	gSpriteClips[2].x = 0;
	gSpriteClips[2].y = 100;
	gSpriteClips[2].w = 100;
	gSpriteClips[2].h = 100;

	//Set bottom right sprite
	gSpriteClips[3].x = 100;
	gSpriteClips[3].y = 100;
	gSpriteClips[3].w = 100;
	gSpriteClips[3].h = 100;

	return true;
}

bool LoadMedia()
{
	bool result = true;
	result &= gTexture1.LoadFromFile(gRenderer, "data/flower.bmp");
	result &= gTexture2.LoadFromFile(gRenderer, "data/foo.png");
	result &= gSpriteSheetTexture.LoadFromFile(gRenderer, "data/sprites.png");
	return result;
}

SDL_Texture* LoadTexture(std::string path)
{
	SDL_Texture *newTexture = nullptr;
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (!loadedSurface)
	{
		LOG_ERROR("Unalbe to load image %s! SDL_Image error: %s", path.c_str(), IMG_GetError());
		return nullptr;
	}

	// Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	if (newTexture == nullptr)
	{
		LOG_ERROR("Unalbe to create texture from %s! SDL error: %s", path.c_str(), IMG_GetError());
	}

	// Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	return newTexture;
}

void Close()
{	
	gTexture1.Free();
	gTexture2.Free();
	gSpriteSheetTexture.Free();

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	// Quit SDL subsystems
	IMG_Quit();
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
	
	
	posX = 0; //(SCREEN_WIDTH - width) / 2;
	posY = 0; //(SCREEN_HEIGHT - height) / 2;	

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

		
		
		// Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);		

		// Render texture to screen
		SDL_Rect topRightViewport = { 0, 0, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3};
		SDL_Rect topLeftViewport = { SCREEN_WIDTH * 2/3, 0, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3 };
		SDL_Rect bottomViewport = { 0, SCREEN_HEIGHT / 3, SCREEN_WIDTH, SCREEN_HEIGHT * 2/3 };
		
		//gTexture1.Render(gRenderer, 0, 0);
		//gTexture2.Render(gRenderer, 100, 100);
		
		//Render top left sprite
		gSpriteSheetTexture.SetColorMod(255, 255, 255);
		gSpriteSheetTexture.Render(gRenderer, 0, 0, &gSpriteClips[0]);

		//Render top right sprite
		gSpriteSheetTexture.Render(gRenderer,SCREEN_WIDTH - gSpriteClips[1].w, 0, &gSpriteClips[1]);
		
		//Render bottom left sprite
		gSpriteSheetTexture.SetColorMod(100, 100, 100);
		gSpriteSheetTexture.Render(gRenderer, 0, SCREEN_HEIGHT - gSpriteClips[2].h, &gSpriteClips[2]);

		//Render bottom right sprite
		gSpriteSheetTexture.Render(gRenderer, SCREEN_WIDTH - gSpriteClips[3].w, SCREEN_HEIGHT - gSpriteClips[3].h, &gSpriteClips[3]);

		DrawPrimitives();

		// Update screen
		SDL_RenderPresent(gRenderer);
	}

	LOG_INFO("End session");

	return 0;
}

void DrawPrimitives()
{
	// Render red filled quad
	SDL_Rect fillRect = { SCREEN_WIDTH * 7 / 16, SCREEN_HEIGHT * 7 / 16, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 8 };
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0, 0, 0xFF);
	SDL_RenderFillRect(gRenderer, &fillRect);

	// Render green outlineed quad
	SDL_Rect outlineRect = { SCREEN_WIDTH * 3 / 8, SCREEN_HEIGHT * 3 / 8, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 };
	SDL_SetRenderDrawColor(gRenderer, 0, 0xFF, 0, 0xFF);
	SDL_RenderDrawRect(gRenderer, &outlineRect);

	// Draw blue horizontal line
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0xFF, 0xFF);
	SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

	// Draw vertical line of yellow dots
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0, 0xFF);
	for (int i = 0; i < SCREEN_HEIGHT; i += 4)
	{
		SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
	}
}

