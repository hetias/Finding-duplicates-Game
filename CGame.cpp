#include"CGame.h"
#include"CCard.h"
#include"CTexture.h"


CCard card_maze[8];
SDL_Point card_positions[8];

int first_card = -1;
int second_card = -1;

int pairs_found = 0;

bool flip_pair = false;

CGame::CGame()
{
	isRunning = true;

	gameRenderer = NULL;
	//gameSurface = NULL;
	gameWindow = NULL;
}

//Game destructor
CGame::~CGame()
{
	Close();
}

//Game Initialize
bool CGame::Initialize(const char* title, int width, int height)
{
	//initialize sdl
	if ( (SDL_Init(SDL_INIT_EVERYTHING)) != 0 )
	{
		printf(".::CANT::INITIALIZE::SDL2::- %s -::.\n", SDL_GetError() );
		return false;
	}

	//initialize sdl image
	if ((IMG_Init(IMG_INIT_PNG)) != IMG_INIT_PNG)
	{
		printf(".::CANT::INITIALIZE::SDL_IMAGE::- %s -::.\n", IMG_GetError());
		return false;
	}

	//create game window
	gameWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, 
								SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	if (gameWindow == NULL)
	{
		printf(".::CANT::CREATE::WINDOW::- %s -::.\n", SDL_GetError());
		return false;
	}

	//create game renderer
	gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gameRenderer == NULL)
	{
		printf(".::CANT::CREATE::RENDERER::- %s -::.\n", SDL_GetError());
		return false;
	}
	return true;
}

//Game File Management
void CGame::Manage()
{
	for(int i = 0; i < 8; i++)
	{
		card_maze[i].LoadTexture(gameRenderer, "textures/cards_spritesheet.png");
	}

	card_positions[0] = { 0,0 };
	card_positions[1] = { 200,0 };
	card_positions[2] = { 400,0 };
	card_positions[3] = { 600,0 };
	card_positions[4] = { 0,300 };
	card_positions[5] = { 200,300 };
	card_positions[6] = { 400,300 };
	card_positions[7] = { 600,300 };

	//define cards positions
	for (int i = 0; i < 8; i++)
	{
		card_maze[i].SetPosition(card_positions[i]);
	}
	
	//define ids
	for (int i = 0; i < 8; i++)
	{
		card_maze[i].SetId(i);
	}
}

//Game Loop
void CGame::Loop()
{
	Manage();
	while (isRunning)
	{
		Logic();
		Render();
		//CleanUp();
	}
}

//Game logic handler
void CGame::Logic()
{
	while (SDL_PollEvent(&gameEvent) != 0)
	{
		//If event is a Quit event, then stop running
		if (gameEvent.type == SDL_QUIT)
		{
			isRunning = false;
		}

		if (first_card == -1)
		{
			int aux = -1;
			for (int i = 0; i < 8; i++)
			{
				aux = card_maze[i].FlipCard(&gameEvent);
				if (aux != -1)
				{
					first_card = aux;
					break;
				}
			}
			
		}
		else if (first_card != -1 && second_card == -1)
		{
			int aux = -1;
			for (int i = 0; i < 8; i++)
			{
				aux = card_maze[i].FlipCard(&gameEvent);
				if (aux != -1 && aux != first_card)
				{
					second_card = aux;
					break;
				}
			}

		}
		
		if (flip_pair && gameEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_Delay(150);

			card_maze[first_card].ResetCard();
			card_maze[second_card].ResetCard();

			first_card = -1;
			second_card = -1;

			flip_pair = false;
		}
	}

	//POST WHILE

	//if we flipped two cards, verify they are pairs. 
	//Add 1 to pairs found if they are
	//flippe them back if not
	if (first_card != -1 && second_card != -1)
	{
		if (first_card == 0 && second_card == 4 || first_card == 4 && second_card == 0)
		{
			printf("pair!\n");
			pairs_found++;

			first_card = -1;
			second_card = -1;
		}
		else if (first_card == 1 && second_card == 5 || first_card == 5 && second_card == 1)
		{
			printf("pair!\n");
			pairs_found++;

			first_card = -1;
			second_card = -1;
		}
		else if(first_card == 2 && second_card == 6 || first_card == 6 && second_card == 2)
		{
			printf("pair!\n");
			pairs_found++;

			first_card = -1;
			second_card = -1;
		}
		else if (first_card == 3 && second_card == 7 || first_card == 7 && second_card == 3)
		{
			printf("pair!\n");
			pairs_found++;

			first_card = -1;
			second_card = -1;
		}
		else
		{
			printf("no pair!\n");
			flip_pair = true;
		}
	}

	if (pairs_found >= 4)
	{
		printf("All pairs found!\n");
		SDL_Delay(150);

		for (int i = 0; i < 8; i++)
		{
			card_maze[i].ResetCard();
			first_card = -1;
			second_card = -1;
		}

		pairs_found = 0;
	}

}

//Game Render
void CGame::Render()
{
	//Clear Renderer
	SDL_SetRenderDrawColor(gameRenderer, 255, 0, 0, 255);
	SDL_RenderClear(gameRenderer);

	for (int i = 0; i < 8; i++)
	{
		card_maze[i].RenderCard(gameRenderer);
	}

	//Updates Renderer
	SDL_RenderPresent(gameRenderer);
}

//File clean up
void CGame::CleanUp()
{
	
}

//Game close
void CGame::Close()
{
	//Destroy renderer
	SDL_DestroyRenderer(gameRenderer);

	//Destroy game window
	SDL_DestroyWindow(gameWindow); //implicit window surface destroy

	//Close SDL and subsystems
	SDL_Quit();
	IMG_Quit();
}