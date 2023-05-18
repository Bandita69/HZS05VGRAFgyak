#include "menu.h"
#include "app.h"

void eventHandler_Menu(SDL_Event event, int *running, int *cat, int *selected)
{
	int x;
	int y;
	while (SDL_PollEvent(&event))
		switch (event.type)
		{
		case SDL_QUIT:
			*running = 1;
			break;
		// case SDL_KEYDOWN:
		// 	switch (event.key.keysym.scancode)
		// 	{
		// 	case SDL_SCANCODE_A:
		// 	case SDL_SCANCODE_LEFT:
		// 		*cat = 1;
		// 		break;
		// 	case SDL_SCANCODE_D:
		// 	case SDL_SCANCODE_RIGHT:
		// 		*cat = 2;
		// 		break;
		// 	case SDL_SCANCODE_S:
		// 	case SDL_SCANCODE_DOWN:
		// 		*cat = 3;
		// 		break;

		// 	case SDL_SCANCODE_SPACE:
		// 		*selected = 1;
		// 		break;
		// 	default:
		// 		break;
		// 	}
		// 	break;
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&x, &y);
		
			if (x >= 50 && x <= 300 && y >= 250 && y <= 390)
			{
				*cat = 1;
				*selected = 1;
			}
			
			if (x >= 350 && x <= 600 && y >= 250 && y <= 390)
			{
				*cat = 2;
				*selected = 1;
			}
			
			if (x >= 50 && x <= 300 && y >= 400 && y <= 540)
			{
				*cat = 3;
				*selected = 1;
			}
			
			if (x >= 350 && x <= 600 && y >= 400 && y <= 540)
			{
				*cat = 4;
				*selected = 1;
			}
			
			if (x >= 50 && x <= 300 && y >= 550 && y <= 690)
			{
				*cat = 5;
				*selected = 1;
			}

			break;
		}
}