#pragma once

class Texture
{
public:
	Texture();
	~Texture();

	bool LoadFromFile(SDL_Renderer* renderer, std::string path);
	void Free();

	void Render(SDL_Renderer* renderer, int x, int y, SDL_Rect* portion = nullptr);

	void SetColorMod(Uint8 red, Uint8 green, Uint8 blue);

	int GetWidth();
	int GetHeight();
	
private:
	SDL_Texture* m_texture = nullptr;
	int m_width = 0;
	int m_height = 0;
};
