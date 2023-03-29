#ifndef GAME_H_
#define GAME_H_

#include <SDL2/SDL.h>
#include "Ball.h"
#include "Pcont.h"

void eventHandler(SDL_Event event, PCONT* player1, PCONT* player2, int* running, int* paused);
void inputHandler(SDL_Event event, int* running, Ball* ball, PCONT* player1, PCONT* player2, char* score_str, int* paused, int* won);

#endif
