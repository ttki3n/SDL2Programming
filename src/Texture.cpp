#include "stdafx.h"

#include "Texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
	Free();
}

bool Texture::LoadFromFile(SDL_Renderer* renderer, std::string path)
{
	// Get rid of preexisting texture
	Free();	

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		LOG_ERROR("Unable to load image %s! SDL_Image error: %s!", path.c_str(), IMG_GetError());
		return false;
	}

	// Color key image
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	// Create texture from surface pixels
	m_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (m_texture == nullptr)
	{
		LOG_ERROR("Unable to create texture from %s! SDL error: %s!", path.c_str(), SDL_GetError());
	}
	else
	{
		m_width = loadedSurface->w;
		m_height = loadedSurface->h;
	}

	// Free loaded surface
	SDL_FreeSurface(loadedSurface);

	return m_texture != nullptr;
}

void Texture::Free()
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}

void Texture::SetColorMod(Uint8 red, Uint8 green, Uint8 blue)
{
	// Set color modulation
	SDL_SetTextureColorMod(m_texture, red, green, blue);
}

void Texture::Render(SDL_Renderer* renderer, int x, int y, SDL_Rect* portion)
{
	// Set rendering space
	SDL_Rect renderQuad = { x, y, m_width, m_height };

	// Set portion rendering
	if (portion != nullptr)
	{
		renderQuad.w = portion->w;
		renderQuad.h = portion->h;
	}

	SDL_RenderCopy(renderer, m_texture, portion, &renderQuad);
}

int Texture::GetWidth()
{
	return m_width;
}

int Texture::GetHeight()
{
	return m_height;
}