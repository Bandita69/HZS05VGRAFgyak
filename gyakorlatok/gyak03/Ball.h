#ifndef BALL_H_
#define BALL_H_

#include <SDL2/SDL.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)
#define BALL_SPAWN_X (WINDOW_WIDTH / 2)
#define BALL_SPAWN_Y (WINDOW_HEIGHT / 2)

typedef struct{
	SDL_Rect rect;
	
	int vel_x;
	int vel_y;
}Ball;

#include "Pcont.h"

void update_ball(Ball* ball, PCONT* player, PCONT* player2, char* score_str);


#endif 
