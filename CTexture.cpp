#include"CTexture.h"
#include<stdio.h>

SDL_Texture* CTexture::LoadTexture(SDL_Renderer* renderer, SDL_bool hasTransparency, const char* file)
{
	SDL_Surface* texSurf = NULL;
	SDL_Texture* finalTex = NULL;
	if ((texSurf = IMG_Load(file)) == NULL)
	{
		printf(".::CANT::CREATE::SURFACE::FROM::%s::.\n", file);
		return NULL;
	}
	else
	{
		//SDL_SetColorKey(texSurf, hasTransparency, SDL_MapRGB(texSurf->format, 0, 255, 0));

		finalTex = SDL_CreateTextureFromSurface(renderer, texSurf);
		if (finalTex == NULL)
		{
			printf(".::CANT::CREATE::TEXTURE::FROM::%s::.\n", file);
			return NULL;
		}
	}

	SDL_FreeSurface(texSurf);

	//printf(".::TEXTURE::SUCCESSFULLY::LOADED::FROM::%s::.\n", file);

	return finalTex;
}

void CTexture::RenderTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect)
{
	SDL_RenderCopy(renderer, texture, srcRect, destRect);
}
