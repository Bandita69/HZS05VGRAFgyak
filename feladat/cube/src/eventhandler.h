#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "app.h"
#include "scene.h"
#include "menu.h"

/**
 * Handle the events of the application.
 */
void handle_app_events(App *app);

#endif /* EVENTHANDLER_H_ */