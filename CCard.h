#ifndef CCARD_H
#define CCARD_H

#include<SDL.h>
#include<stdio.h>
#include"CTexture.h"

class CCard {
public:

	CCard();
	~CCard();
	void LoadTexture(SDL_Renderer* gameRenderer, const char* file);
	void RenderCard(SDL_Renderer* gameRenderer);
	int FlipCard(SDL_Event* e);
	void ResetCard();
	void SetId(int a);
	int  GetId();
	void SetPosition(SDL_Point pos);

private:
	int cardId;
	int width, height;
	int x, y;
	bool isShowing;
	SDL_Texture* cardTexture;

	SDL_Rect card_dimensions;

	SDL_Rect green_card;
	SDL_Rect red_card;
	SDL_Rect blue_card;
	SDL_Rect purple_card;
	SDL_Rect gray_card;
};

#endif
