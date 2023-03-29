#include "Game.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include "Ball.h"
#include "Pcont.h"
#include "Renderer.h"

// amig lenyomva van a gomb, addig mozog a player + escape gombbal lehet pauseolni
void eventHandler(SDL_Event event, PCONT *player1, PCONT *player2, int *running, int *paused)
{
	while (SDL_PollEvent(&event))
		switch (event.type)
		{
		case SDL_QUIT:
			*running = 1;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_W:
				player1->controls[0] = 1;
				break;
			case SDL_SCANCODE_UP:
				player2->controls[0] = 1;
				break;
			case SDL_SCANCODE_S:
				player1->controls[1] = 1;
				break;
			case SDL_SCANCODE_DOWN:
				player2->controls[1] = 1;
				break;
			case SDL_SCANCODE_ESCAPE:
				*paused *= -1;
				break;
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_W:
				player1->controls[0] = 0;
				break;
			case SDL_SCANCODE_UP:
				player2->controls[0] = 0;
				break;
			case SDL_SCANCODE_S:
				player1->controls[1] = 0;
				break;
			case SDL_SCANCODE_DOWN:
				player2->controls[1] = 0;
				break;
			default:
				break;
			}
		}
}

void inputHandler(SDL_Event event, int *running, Ball *ball, PCONT *player1, PCONT *player2, char *score_str, int *paused, int *won)
{
	// Input kezeles + nyerteshirdetés
	eventHandler(event, player1, player2, running, paused);
	if (*paused == -1)
	{
		*won = 0;
		// Player mozgás
		playerControls(player1);
		playerControls(player2);
		// Ball mozgás
		update_ball(ball, player1, player2, score_str);

		// Kinyert eldöntése
		if (player1->score >= 5 || player2->score >= 5)
		{

			*paused *= -1;

			if (player1->score >= 5)

				*won = 1;
			if (player2->score >= 5)

				*won = 2;
			player1->score = 0;
			player2->score = 0;
			sprintf(score_str, "%d  %d", player1->score, player2->score);
		}
	}
}
