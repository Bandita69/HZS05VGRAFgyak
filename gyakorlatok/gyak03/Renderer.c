#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Renderer.h"

// mindenféle inicializálás
int Init(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return 1;
	}
	if (Window_Init(window) != 0)
		return 1;
	if (Renderer_Init(renderer, *window) != 0)
		return 1;
	if (Font_Init(font, *renderer, *window) != 0)
		return 1;
	return 0;
}

int Window_Init(SDL_Window **window)
{
	*window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	if (!*window)
	{
		printf("Error initializing window: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	return 0;
}

int Renderer_Init(SDL_Renderer **renderer, SDL_Window *window)
{
	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	*renderer = SDL_CreateRenderer(window, -1, render_flags);
	if (!*renderer)
	{
		printf("Error initializing renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	return 0;
}
// a fontnak a workspace-ban kell lennie, ahol a program fut
int Font_Init(TTF_Font **font, SDL_Renderer *renderer, SDL_Window *window)
{
	TTF_Init();
	*font = TTF_OpenFont("arial.ttf", 24);
	if (!*font)
	{
		printf("Error initializing font: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}
	return 0;
}
// objektumok felszabadítása
void quit(SDL_Renderer *renderer, SDL_Window *window, TTF_Font *font)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	SDL_Quit();
	TTF_Quit();
}
// a játék közbeni pontszám kiírása
void renderScore(SDL_Renderer *renderer, const char *score_str, TTF_Font *font, SDL_Rect *rect, SDL_Color *color)
{
	SDL_Surface *surface;
	SDL_Texture *texture;
	surface = TTF_RenderText_Solid(font, score_str, *color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	rect->x = (WINDOW_WIDTH / 2) - 20;
	rect->y = 0;
	rect->w = surface->w;
	rect->h = surface->h;
	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, rect);
	SDL_DestroyTexture(texture);
}

void reFresh(SDL_Renderer *renderer)
{
	SDL_RenderPresent(renderer);
	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // fekete
	SDL_RenderClear(renderer); 
	SDL_Delay(1000 / 60); // "fps" limit
	return;
}

void drawGame(SDL_Renderer *renderer, PCONT player, PCONT player2, Ball ball)
{

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // fehér
	SDL_Rect *player_rect = &player.rect;
	SDL_Rect *player2_rect = &player2.rect;
	SDL_Rect *ball_rect = &ball.rect;
	SDL_RenderFillRect(renderer, player_rect);
	SDL_RenderFillRect(renderer, player2_rect);
	// SDL_RenderFillRect(renderer, ball_rect); // ez a négyzet, de körrel akartam kirajzolni
	drawCircle(renderer, ball_rect->x + ball_rect->w / 2, ball_rect->y + ball_rect->w / 2, ball_rect->w / 2, 1); // ez a kör
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);															 // zöld
	// felezővonal: 3x vastagságú, hogy látszódjon
	SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);
	SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2 + 1, 0, WINDOW_WIDTH / 2 + 1, WINDOW_HEIGHT);
	SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2 - 1, 0, WINDOW_WIDTH / 2 - 1, WINDOW_HEIGHT);
	return;
}
// ez a függvény rajzolja ki a "Paused" feliratot
void drawPaused(SDL_Renderer *renderer, TTF_Font *font, char *text)
{
	SDL_Color White = {255, 255, 255};
	SDL_Surface *surface = TTF_RenderText_Solid(font, text, White);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect pause_rect = {(WINDOW_WIDTH / 2) - 150, WINDOW_HEIGHT / 2 - 150, 300, 200};
	SDL_RenderCopy(renderer, texture, NULL, &pause_rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void drawCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius, int szin)
{
	// ez a függvény rajzol egy köröt a megadott koordinátákra és sugárral
	//  A kör egy nyolcadát rajzolja ki, majd a többi nyolcadat a megfelelő tükrözéssel.
	// a diameter változóban tároljuk a sugár kétszeresét, hogy ne kelljen minden ciklusban szorozni
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;

	int32_t tx = 1;
	int32_t ty = 1;
	// az error változóban tároljuk a kör alakját, hogy a következő pontot melyik irányba kell keresni
	int32_t error = (tx - diameter);


	int sec = 0;
	// ettől pörög
	int sec2 = SDL_GetTicks() / 100;
	int max = 0;
	if (sec2 % 5 == 0 || sec2 % 5 == 1 || sec2 % 5 == 2)
	{
		max = 3;
	}
	else
	{
		max = 5;
	}
	if (szin)
	{
		for (int w = 0; w < diameter; w++)
		{
			for (int h = 0; h < diameter; h++)
			{
				int dx = radius - w; // horizontal offset
				int dy = radius - h; // vertical offset
				if ((dx * dx + dy * dy) <= (radius * radius))
				{
					
					sec ++;
					if (sec % max == 0)
					{
						SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // 		fehér
						sec = 0;
					}
					else
					{ 
						
						SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // fekete
					}

					SDL_RenderDrawPoint(renderer, centreX + dx, centreY + dy);
				}
			}
		}
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // fehér
	while (x >= y)
	{
		//  Ezek a pontok a kör egy-egy nyolcadát rajzolják ki.
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

		// ez az error kezelés a Bresenham algoritmusból származik
		//  https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
		//  https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}
