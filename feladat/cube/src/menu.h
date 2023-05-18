#ifndef MENU_H_
#define MENU_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "app.h"



void eventHandler_Menu(SDL_Event event, int* running, int* cat, int* selected);

#endif /* MENU_H_ */