#ifndef CGAME_H
	#define CGAME_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<SDL.h>
#include<SDL_image.h>

void define_cards_pos();

enum GAME_STATE {
	GAME_RUNING,
	RESET_CARDS,
	GAME_END
};

class CGame
{
public:
	//Game constructor
	CGame();

	//Game destructor
	~CGame();

	//Game Initialize
	bool Initialize(const char* title, int width, int height);

	//Game File Management
	void Manage();

	//Game Loop
	void Loop();

	//Game logic handler
	void Logic();

	//Game Render
	void Render();

	//File clean up
	void CleanUp();

	//Game close
	void Close();

private:

	SDL_Renderer* gameRenderer;
	SDL_Window* gameWindow;
	
	bool isRunning;
	SDL_Event gameEvent;
};

#endif // !CGAME_H
