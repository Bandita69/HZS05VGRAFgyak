#ifndef RENDERER_H_
#define RENDERER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Ball.h"
#include "Pcont.h"

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

int Init(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font);
int Window_Init(SDL_Window **window);
int Renderer_Init(SDL_Renderer **renderer, SDL_Window *window);
int Font_Init(TTF_Font **font, SDL_Renderer *renderer, SDL_Window *window);
void quit(SDL_Renderer *renderer, SDL_Window *window, TTF_Font *font);
void renderScore(SDL_Renderer *renderer, const char *score_str, TTF_Font *font, SDL_Rect *rect, SDL_Color *color);
void reFresh(SDL_Renderer *renderer);
void drawGame(SDL_Renderer *renderer, PCONT player, PCONT player2, Ball ball);
void drawPaused(SDL_Renderer *renderer, TTF_Font *font, char * text);
void drawCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius, int szin);
#endif 
