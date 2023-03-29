#ifndef PCONT_H_
#define PCONT_H_

#include <SDL2/SDL.h>
#include "Ball.h"

typedef struct{
	SDL_Rect rect;
	int score;
	int controls[2];
}PCONT;

void playerControls(PCONT* player);

#endif 
