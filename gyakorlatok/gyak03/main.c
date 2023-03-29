#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Renderer.h"
#include "Ball.h"
#include "Pcont.h"
#include "Game.h"

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)
#define SPEED (3) // 3 - slow 4 - medium 6 - fast
#define BALL_START_X (WINDOW_WIDTH / 2)
#define BALL_START_Y (WINDOW_HEIGHT / 2)

int main(int argc, char **argv)
{
	// SDL Initialization **************************************************
	SDL_Window *window;
	SDL_Renderer *renderer;
	TTF_Font *font;
	Init(&window, &renderer, &font);

	// Game ******************************************************

	// Player1 **************************************************
	PCONT player1;
	SDL_Rect player_rect = {0, WINDOW_HEIGHT / 2, 16, 64};
	player1.rect = player_rect;
	player1.score = 0;
	player1.controls[0] = player1.controls[1] = 0;

	// Player 2 **************************************************
	PCONT player2;
	player_rect.x = WINDOW_WIDTH - 16;
	player2.rect = player_rect;
	player2.score = 0;
	player2.controls[0] = player2.controls[1] = 0;

	// Ball **************************************************
	Ball ball;
	ball.vel_x = SPEED;
	ball.vel_y = SPEED;
	SDL_Rect ball_rect = {BALL_START_X, BALL_START_Y, 24, 24};
	ball.rect = ball_rect;

	// Scoreboard **************************************************
	SDL_Color White = {255, 255, 255};
	char score_str[5];
	sprintf(score_str, "%d  %d", player1.score, player2.score);
	SDL_Rect score_rect;

	// Event Handling *********************************************
	int running = 0;
	int paused = -1;
	int won = 0;
	SDL_Event event;

	// Game Loop ***********************************************************

	while (!running)
	{

		inputHandler(event, &running, &ball, &player1, &player2, score_str, &paused, &won);
		renderScore(renderer, score_str, font, &score_rect, &White);
		drawGame(renderer, player1, player2, ball);
		if (paused == 1 && won == 0)
			drawPaused(renderer, font, "Paused");
		if (won == 1)
			drawPaused(renderer, font, "Player 1 Won!");
		if (won == 2)	
			drawPaused(renderer, font, "Player 2 Won!");


		// Next frame
		reFresh(renderer);
	}

	// Release Resources ***************************************************
	quit(renderer, window, font);
	return 0;
}
