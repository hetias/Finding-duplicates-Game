#ifndef CTEXTURE_H
#define CTEXTURE_H

#include<SDL.h>
#include<SDL_image.h>

class CTexture 
{
public:
	static SDL_Texture* LoadTexture(SDL_Renderer* renderer, SDL_bool transparency, const char* texture_file);
	static void RenderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect );
};

#endif
