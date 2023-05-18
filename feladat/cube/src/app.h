#ifndef APP_H
#define APP_H

#include "camera.h"
#include "scene.h"
#include "menu.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


#include <stdbool.h>

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

typedef struct App
{
    SDL_Window* window;
    SDL_GLContext gl_context;
    bool is_running;
    double uptime;
    Camera camera;
    Scene scene;
    Mix_Chunk *meow;
    Mix_Chunk *purr;
    Mix_Chunk *yawn;
    Mix_Chunk *purr2;
 
} App;

int Init(SDL_Window** window, SDL_Renderer** renderer, TTF_Font** font);
int Window_Init(SDL_Window** window);
int Renderer_Init(SDL_Renderer** renderer, SDL_Window* window);
int Font_Init(TTF_Font** font, SDL_Renderer* renderer, SDL_Window* window);
void drawMenu(SDL_Renderer *renderer, TTF_Font* font, int cats, char* menuCatWhite_texture_path, char* menuCatThree_texture_path, char * menuCatBlack_texture_path, char * menuCatRed_texture_path);
void redraw(SDL_Renderer* renderer);
void quit(SDL_Renderer* renderer, SDL_Window* window, TTF_Font* font);


/**
 * Initialize the application.
 */
void init_app(App* app, int width, int height, char *model_texture_path, char* background_texture_path, Model * model_rats, Model * model_look, Model* model_stand_sit, Model * model_sit, Model * model_sit_stand, Model * model_sit_look,  Model *model_stand_yawn);

/**
 * Initialize the OpenGL context.
 */
void init_opengl();

/**
 * Reshape the window.
 */
void reshape(GLsizei width, GLsizei height);



/**
 * Update the application.
 */
void update_app(App* app);

/**
 * Render the application.
 */
void render_app(App* app, Model * model_rats);

/**
 * Destroy the application.
 */
void destroy_app(App* app);

#endif /* APP_H */
