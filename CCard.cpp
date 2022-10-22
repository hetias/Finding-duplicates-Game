#include"CCard.h"

CCard::CCard()
{
	x = 0;
	y = 0;
	width = 200;
	height = 300;
	isShowing = false;
    cardId = 0;
    cardTexture = NULL;

    card_dimensions = { x, y, width, height};

    green_card = { 0,0,card_dimensions.w, card_dimensions.h };
    red_card = { card_dimensions.w,0,card_dimensions.w, card_dimensions.h };
    blue_card = { card_dimensions.w * 2,0,card_dimensions.w, card_dimensions.h };
    purple_card = { card_dimensions.w * 3,0,card_dimensions.w, card_dimensions.h };
    gray_card = { 0,card_dimensions.h  ,card_dimensions.w, card_dimensions.h };

}

CCard::~CCard()
{
    //printf("Card  texture destroyed!\n");
    SDL_DestroyTexture(cardTexture);
    cardTexture = NULL;
}

void CCard::LoadTexture(SDL_Renderer* gr, const char* file)
{
	cardTexture = CTexture::LoadTexture(gr, SDL_FALSE, file);
}

void CCard::RenderCard(SDL_Renderer* gr)
{
    card_dimensions.x = x;
    card_dimensions.y = y;

    if (isShowing)
    {
        switch (cardId)
        {
        case 0:
            CTexture::RenderTexture(gr, cardTexture, &green_card, &card_dimensions);
            break;
        case 1:
            CTexture::RenderTexture(gr, cardTexture, &red_card, &card_dimensions);
            break;
        case 2:
            CTexture::RenderTexture(gr, cardTexture, &blue_card, &card_dimensions);
            break;
        case 3:
            CTexture::RenderTexture(gr, cardTexture, &purple_card, &card_dimensions);
            break;
        case 4:
            CTexture::RenderTexture(gr, cardTexture, &green_card, &card_dimensions);
            break;
        case 5:
            CTexture::RenderTexture(gr, cardTexture, &red_card, &card_dimensions);
            break;
        case 6:
            CTexture::RenderTexture(gr, cardTexture, &blue_card, &card_dimensions);
            break;
        case 7:
            CTexture::RenderTexture(gr, cardTexture, &purple_card, &card_dimensions);
            break;
        default:
            CTexture::RenderTexture(gr, cardTexture, &gray_card, &card_dimensions);
            break;
        }
	}
	else
	{
        CTexture::RenderTexture(gr,cardTexture, &gray_card, &card_dimensions);
    }
}

int CCard::FlipCard(SDL_Event* e) {
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN) {

        int _x, _y;
        SDL_GetMouseState(&_x, &_y);

        bool inside = true;

        if (_x < x) {
            inside = false;
        }
        else if (_x > x + width) {
            inside = false;
        }
        else if (_y < y) {
            inside = false;
        }
        else if (_y > y + height) {
            inside = false;
        }

        if (inside) {
            if (e->type == SDL_MOUSEBUTTONDOWN) {
                isShowing = true;
                printf("Returned: %d\n", cardId);
                return cardId;
            }
        }
        else
        {
            return -1;
        }
    }

    return -1;
}

void CCard::SetId(int a)
{
    cardId = a;
}

int CCard::GetId()
{
    return cardId;
}

void CCard::SetPosition(SDL_Point pos)
{
    x = pos.x;
    y = pos.y;
}

void CCard::ResetCard()
{
    isShowing = false;
}