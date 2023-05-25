#include "app.h"
#include "scene.h"
#include "model.h"
#include <stdio.h>
#include <obj/load.h>
#include <obj/draw.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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
    *window = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 700, SDL_WINDOW_OPENGL);
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

void drawMenu(SDL_Renderer *renderer, TTF_Font *font, int cat, char *menuCatWhite_texture_path, char *menuCatThree_texture_path, char *menuCatBlack_texture_path, char *menuCatRed_texture_path)
{

    SDL_Color color;
    SDL_Color White = {255, 255, 255, 0};
    SDL_Color Grey = {169, 169, 169, 0};
    // load image
    SDL_Surface *image = IMG_Load("assets/textures/menu/test.png");
    SDL_Surface *surface;
    // SDL_Surface *surface = TTF_RenderText_Solid(font, "Teszt!", White);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect cat_rect1 = {250, 0, 300, 200};
    SDL_RenderCopy(renderer, texture, NULL, &cat_rect1);
    // controls text
    char *text1 = "Controls";
    char *text2 = " - WS kamera elore/hatra";
    char *text3 = " - RF kamera le/fel";
    char *text4 = " - AD kamera jobbra/balra";
    char *text5 = " - Q kamera alaphelyzet";
    char *text6 = " - ESC kilepes";
    surface = TTF_RenderText_Solid(font, text1, White);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect cat_rect61 = {50, 25, 100, 20};
    SDL_RenderCopy(renderer, texture, NULL, &cat_rect61);
    surface = TTF_RenderText_Solid(font, text2, White);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect cat_rect71 = {50, 50, 150, 20};
    SDL_RenderCopy(renderer, texture, NULL, &cat_rect71);
    surface = TTF_RenderText_Solid(font, text3, White);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect cat_rect8 = {50, 75, 150, 20};
    SDL_RenderCopy(renderer, texture, NULL, &cat_rect8);
    surface = TTF_RenderText_Solid(font, text4, White);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect cat_rect9 = {50, 100, 150, 20};
    SDL_RenderCopy(renderer, texture, NULL, &cat_rect9);
    surface = TTF_RenderText_Solid(font, text5, White);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect cat_rect10 = {50, 125, 150, 20};
    SDL_RenderCopy(renderer, texture, NULL, &cat_rect10);
    surface = TTF_RenderText_Solid(font, text6, White);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect cat_rect11 = {50, 150, 100, 20};
    SDL_RenderCopy(renderer, texture, NULL, &cat_rect11);
    // surface = TTF_RenderText_Solid(font, "Controls: \n * WS kamera elore/hatra \n * RF kamera le/fel \n * AD kamera jobbra/balra \n * Q kamera alaphelyzet", White);

    if (cat == 1)
        color = White;
    else
        color = Grey;
    surface = TTF_RenderText_Solid(font, "Exit", color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect cat_rect2 = {50, 250, 250, 140}; // x = 50 y = 250 w = 250 h = 140
    SDL_RenderCopy(renderer, texture, NULL, &cat_rect2);
    if (cat == 2)
        color = White;
    else
        color = Grey;
    image = IMG_Load(menuCatWhite_texture_path);
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect cat_rect3 = {350, 250, 250, 140}; // x = 350 y = 250 w = 250 h = 140
    SDL_RenderCopy(renderer, texture, NULL, &cat_rect3);
    if (cat == 3)
        color = White;
    else
        color = Grey;
    image = IMG_Load(menuCatThree_texture_path);
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect cat_rect4 = {50, 400, 250, 140}; // x = 50 y = 400 w = 250 h = 140
    SDL_RenderCopy(renderer, texture, NULL, &cat_rect4);
    if (cat == 4)
        color = White;
    else
        color = Grey;
    image = IMG_Load(menuCatBlack_texture_path);
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect cat_rect5 = {350, 400, 250, 140}; // x = 350 y = 400 w = 250 h = 140
    SDL_RenderCopy(renderer, texture, NULL, &cat_rect5);
    if (cat == 5)
        color = White;
    else
        color = Grey;
    image = IMG_Load(menuCatRed_texture_path);
    texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect cat_rect6 = {50, 550, 250, 140}; // x = 50 y = 550 w = 250 h = 140
    SDL_RenderCopy(renderer, texture, NULL, &cat_rect6);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void redraw(SDL_Renderer *renderer)
{
    SDL_RenderPresent(renderer);
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_Delay(1000 / 60);


    return;
}

void quit(SDL_Renderer *renderer, SDL_Window *window, TTF_Font *font)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    SDL_Quit();
    TTF_Quit();
    return;
}

void init_app(App *app, int width, int height, char *model_texture_path, char *background_texture_path, Model *model_rats, Model *model_look, Model *model_stand_sit, Model *model_sit, Model *model_sit_stand, Model *model_sit_look, Model *model_stand_yawn, Model * model_shadow)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0)
    {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "Relax!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL)
    {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0)
    {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL)
    {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene), model_texture_path, background_texture_path, model_rats, model_look, model_stand_sit, model_sit, model_sit_stand, model_sit_look, model_stand_yawn, model_shadow);

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    // glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    // glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO)
    {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else
    {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 10);
}

void update_app(App *app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene));



}

void render_app(App *app, Model *model_rats, Model * model_shadows)

{

  

    if (app->scene.frame_draw < app->scene.end_frame && SDL_GetTicks() % 30 == 0)
    {
        app->scene.frame_draw++;
    }

    if (app->scene.frame_draw == app->scene.end_frame)
    {

        if (app->scene.animate == 1 && SDL_GetTicks() % 50 == 0) // leül
        {
            app->scene.animate = 3;
        }
        else if (app->scene.animate == 1 && SDL_GetTicks() % 45 == 0) // nézelődik
        {
            app->scene.animate = 2;

            Mix_PlayChannel(-1, app->meow, 0);
        }
        else if (app->scene.animate == 1 && SDL_GetTicks() % 30 == 0) // ásít
        {

            app->scene.animate = 7;

            Mix_PlayChannel(-1, app->yawn, 0);
        }
        else if (app->scene.animate == 2 || app->scene.animate == 7) // álldogál
        {
            app->scene.animate = 1;
        }
        else if (app->scene.animate == 3) // üldögél
        {
            app->scene.animate = 4;

            Mix_PlayChannel(-1, app->purr, 0);
        }
        else if (app->scene.animate == 4 && SDL_GetTicks() % 50 == 0) // feláll
        {
            app->scene.animate = 5;
            Mix_PlayChannel(-1, app->meow, 0);
        }
        else if (app->scene.animate == 5) // álldogál
        {
            app->scene.animate = 1;
        }

        else if (app->scene.animate == 4 && SDL_GetTicks() % 45 == 0) // nézelődik
        {
            app->scene.animate = 6;
            Mix_PlayChannel(-1, app->purr2, 0);
        }
        else if (app->scene.animate == 6)
        {
            app->scene.animate = 4;
        }

        app->scene.frame_draw = 1;
    }

    // light_x and light_z are the coordinates of the light source move in semi circle around the scene max 5 units
    if (SDL_GetTicks() % 100 == 0)
    {

        app->scene.light_z = 6 * sin(degree_to_radian(app->scene.light_angle));
        app->scene.light_x = -6 * cos(degree_to_radian(app->scene.light_angle));

        // light color changes with the angle of the light source
        app->scene.diff_g = 100.0f + (app->scene.light_z / 6) * 128.0f;
        app->scene.diff_b = 50.0f + (app->scene.light_z / 6) * 156.0f;

        // shadow moves opposite direction of the light source
        app->scene.shadow_angle = app->scene.light_angle + 180;

        app->scene.light_angle += 2;

        if (app->scene.light_angle == 180)
        {
            app->scene.light_angle = 0;
        }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // ez már itt valami

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    // glLoadIdentity(); // ez ide valami furát csinál

    set_view(&(app->camera));

    render_scene(&(app->scene), model_rats, model_shadows);
    glNormal3f(1, 1, 1);

    free_model(&(app->scene).rat);
    glPopMatrix();

    // if (app->camera.is_preview_visible)
    // {
    //     show_texture_preview();
    // }

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App *app)
{
    if (app->gl_context != NULL)
    {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL)
    {
        SDL_DestroyWindow(app->window);
    }

    // SDL_Quit();
}
