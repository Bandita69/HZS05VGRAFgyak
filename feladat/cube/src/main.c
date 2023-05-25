#include "app.h"
#include "menu.h"
#include "eventhandler.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <stdio.h>

/**
 * Main function
 */
int main(int argc, char *argv[])
{
    App app;
    app.scene.frame = 1;
    app.scene.frame_draw = 1;
    app.scene.loaded = 0;
    app.scene.light_x = 5;
    app.scene.light_y = 0;
    app.scene.light_z = 0;
    app.scene.light_angle = 0;
    app.scene.diff_r = 255;
    app.scene.diff_g = 1;
    app.scene.diff_b = 1;

    app.scene.shadow_x = 0;
    app.scene.shadow_y = 0;
    app.scene.shadow_z = 0;

    struct Model model_stand[100];
    struct Model model_look[100];
    struct Model model_stand_sit[100];
    struct Model model_sit[100];
    struct Model model_sit_stand[100];
    struct Model model_sit_look[100];
    struct Model model_stand_yawn[100];
    struct Model model_shadow[10];

    app.scene.stand = "assets/models/cat/cat_stand_idle/cat_stand_idle_0000%d.obj";
    app.scene.look = "assets/models/cat/cat_stand_look/cat_stand_look_0000%d.obj";
    app.scene.sit = "assets/models/cat/cat_stand_sit/cat_stand_sit_0000%d.obj";
    app.scene.sitting = "assets/models/cat/cat_sit_idle/cat_sit_idle_0000%d.obj";
    app.scene.standing = "assets/models/cat/cat_sit_stand/cat_sit_stand_0000%d.obj";
    app.scene.look_sit = "assets/models/cat/cat_sit_look/cat_sit_look_0000%d.obj";
    app.scene.yawn = "assets/models/cat/cat_stand_yawn/cat_stand_yawn_0000%d.obj";

    app.scene.shadow_texture_path = "assets/textures/shadow.png";

    // struct array

    // SDL Initialization
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    Init(&window, &renderer, &font);

    // music init
    if (Mix_Init(0))
    {
        printf("Error initializing music: %s\n", Mix_GetError());
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("Error initializing music: %s\n", Mix_GetError());
    }
    // Race_Against_the_Sunset.mp3
    Mix_Music *sunset = Mix_LoadMUS("assets/music/Race_Against_the_Sunset.mp3");
    if (!sunset)
    {
        printf("Error initializing music: %s\n", Mix_GetError());
    }
    // animal_rest.mp3
    Mix_Music *rest = Mix_LoadMUS("assets/music/animal_rest.mp3");
    if (!rest)
    {
        printf("Error initializing music: %s\n", Mix_GetError());
    }
    
    // cat_soup.mp3
    Mix_Music *soup = Mix_LoadMUS("assets/music/cat_soup.mp3");
    if (!soup)
    {
        printf("Error initializing music: %s\n", Mix_GetError());
    }
    // classroom.mp3
    Mix_Music *classroom = Mix_LoadMUS("assets/music/classroom.mp3");
    if (!classroom)
    {
        printf("Error initializing music: %s\n", Mix_GetError());
    }
    // garden.mp3
    Mix_Music *garden = Mix_LoadMUS("assets/music/garden.mp3");
    if (!garden)
    {
        printf("Error initializing music: %s\n", Mix_GetError());
    }
    // rain_bird.mp3
    Mix_Music *rain_bird = Mix_LoadMUS("assets/music/rain_bird.mp3");
    if (!rain_bird)
    {
        printf("Error initializing music: %s\n", Mix_GetError());
    }

    // sound effects
    //  cat_meow.wav
    Mix_Chunk *meow = Mix_LoadWAV("assets/music/cat_meow.wav");
    if (!meow)
    {
        printf("Error initializing music: %s\n", Mix_GetError());
    }
    Mix_VolumeChunk(meow, 80);
    app.meow = meow;
    //  cat_purr.wav
    Mix_Chunk *purr = Mix_LoadWAV("assets/music/cat_purr.wav");
    if (!purr)
    {
        printf("Error initializing music: %s\n", Mix_GetError());
    }
    Mix_VolumeChunk(purr, 100);
    app.purr = purr;
    // cat_purr2.mp3
    Mix_Chunk *purr2 = Mix_LoadWAV("assets/music/cat_purr2.mp3");
    if (!purr2)
    {
        printf("Error initializing music: %s\n", Mix_GetError());
    }
    Mix_VolumeChunk(purr2, 100);
    app.purr2 = purr2;
    // cat_yawn.mp3
    Mix_Chunk *yawn = Mix_LoadWAV("assets/music/cat_yawn.mp3");
    if (!yawn)
    {
        printf("Error initializing music: %s\n", Mix_GetError());
    }
    Mix_VolumeChunk(yawn, 120);
    app.yawn = yawn;

    // Menu Variables
    int selected = 0;
    SDL_Event event;
    int running = 0;

    int cat = 1;
    char *menuCatWhite_texture_path = "assets/textures/menu/menuCatWhite.jpg";
    char *menuCatThree_texture_path = "assets/textures/menu/menuCatThree.jpg";
    char *menuCatBlack_texture_path = "assets/textures/menu/menuCatBlack.jpg";
    char *menuCatRed_texture_path = "assets/textures/menu/menuCatRed.jpg";
    Mix_PlayMusic(sunset, -1);
    while (!running)
    {

        if (selected == 0)
        {

            eventHandler_Menu(event, &running, &cat, &selected);
            drawMenu(renderer, font, cat, menuCatWhite_texture_path, menuCatThree_texture_path, menuCatBlack_texture_path, menuCatRed_texture_path);
        }
        else
        {

            if (cat == 5) // piros cica cat island
            {

                app.scene.animate = 1;
                app.scene.frame = 0;
                app.scene.end_frame = 69;

                char *model_texture_path = "assets/textures/European3Cat_eyes.jpg";
                char *background_texture_path = "assets/textures/cat_island.jpg";

                Mix_VolumeMusic(50);

                init_app(&app, 700, 600, model_texture_path, background_texture_path, model_stand, model_look, model_stand_sit, model_sit, model_sit_stand, model_sit_look, model_stand_yawn, model_shadow);
                Mix_PlayMusic(soup, -1);
                while (app.is_running)
                {

                    handle_app_events(&app);
                    update_app(&app);

                    if (SDL_GetTicks() % 10 == 0)
                    {
                        switch (app.scene.animate)
                        {
                        case 1:
                            render_app(&app, model_stand, model_shadow);
                            break;
                        case 2:
                            render_app(&app, model_look, model_shadow);
                            break;
                        case 3:
                            render_app(&app, model_stand_sit, model_shadow);
                            break;
                        case 4:
                            render_app(&app, model_sit, model_shadow);
                            break;
                        case 5:
                            render_app(&app, model_sit_stand, model_shadow);
                            break;
                        case 6:
                            render_app(&app, model_sit_look, model_shadow);
                            break;
                        case 7:
                            render_app(&app, model_stand_yawn, model_shadow);
                            break;

                        default:
                            break;
                        }
                    }
                }
                destroy_app(&app);
                Mix_HaltChannel(-1);
                Mix_PlayMusic(sunset, -1);

                selected = 0;
                cat = 1;
            }

            if (cat == 4) // fekete cica forest
            {
                app.scene.animate = 1;
                app.scene.frame = 0;
                app.scene.end_frame = 69;

                char *model_texture_path = "assets/textures/black_cat_texture_eyes.jpg";
                char *background_texture_path = "assets/textures/forest23.jpg";

                init_app(&app, 700, 600, model_texture_path, background_texture_path, model_stand, model_look, model_stand_sit, model_sit, model_sit_stand, model_sit_look, model_stand_yawn, model_shadow);
                Mix_PlayMusic(garden, -1);
                while (app.is_running)
                {

                    handle_app_events(&app);
                    update_app(&app);

                    if (SDL_GetTicks() % 10 == 0)
                    {
                        switch (app.scene.animate)
                        {
                        case 1:
                            render_app(&app, model_stand, model_shadow);
                            break;
                        case 2:
                            render_app(&app, model_look, model_shadow);
                            break;
                        case 3:
                            render_app(&app, model_stand_sit, model_shadow);
                            break;
                        case 4:
                            render_app(&app, model_sit, model_shadow);
                            break;
                        case 5:
                            render_app(&app, model_sit_stand, model_shadow);
                            break;
                        case 6:
                            render_app(&app, model_sit_look, model_shadow);
                            break;
                        case 7:
                            render_app(&app, model_stand_yawn, model_shadow);
                            break;

                        default:
                            break;
                        }
                    }
                }
                destroy_app(&app);
                Mix_HaltChannel(-1);
                Mix_PlayMusic(sunset, -1);

                selected = 0;
                cat = 1;
            }

            if (cat == 3) // három szinu cica egyetem rain
            {
                app.scene.animate = 1;
                app.scene.frame = 0;
                app.scene.end_frame = 69;

                char *model_texture_path = "assets/textures/ThreeColoredCat_eyes.jpg";
                char *background_texture_path = "assets/textures/egyetem_rain.jpg";

                init_app(&app, 700, 600, model_texture_path, background_texture_path, model_stand, model_look, model_stand_sit, model_sit, model_sit_stand, model_sit_look, model_stand_yawn, model_shadow);
                Mix_PlayMusic(rain_bird, -1);
                while (app.is_running)
                {

                    handle_app_events(&app);
                    update_app(&app);

                    if (SDL_GetTicks() % 10 == 0)
                    {
                        switch (app.scene.animate)
                        {
                        case 1: // ide esetleg jöhetnének a különböző frame számok
                            render_app(&app, model_stand, model_shadow);
                            break;
                        case 2:
                            render_app(&app, model_look, model_shadow);
                            break;
                        case 3:
                            render_app(&app, model_stand_sit, model_shadow);
                            break;
                        case 4:
                            render_app(&app, model_sit, model_shadow);
                            break;
                        case 5:
                            render_app(&app, model_sit_stand, model_shadow);
                            break;
                        case 6:
                            render_app(&app, model_sit_look, model_shadow);
                            break;
                        case 7:
                            render_app(&app, model_stand_yawn, model_shadow);
                            break;

                        default:
                            break;
                        }
                    }
                }
                destroy_app(&app);
                Mix_HaltChannel(-1);
                Mix_PlayMusic(sunset, -1);

                selected = 0;
                cat = 1;
            }

            if (cat == 2) // fehért cica playhouse
            {
                app.scene.animate = 1;
                app.scene.frame = 1;
                app.scene.end_frame = 69;

                char *model_texture_path = "assets/textures/white_cat_eyes.jpg";
                char *background_texture_path = "assets/textures/playhouse.jpg";

                init_app(&app, 700, 600, model_texture_path, background_texture_path, model_stand, model_look, model_stand_sit, model_sit, model_sit_stand, model_sit_look, model_stand_yawn, model_shadow);
                Mix_PlayMusic(rest, -1);
                while (app.is_running)
                {
                    handle_app_events(&app);
                    update_app(&app);
                    if (SDL_GetTicks() % 10 == 0)
                    {
                        switch (app.scene.animate)
                        {
                        case 1:
                            render_app(&app, model_stand, model_shadow);
                            break;
                        case 2:
                            render_app(&app, model_look, model_shadow);
                            break;
                        case 3:
                            render_app(&app, model_stand_sit, model_shadow);
                            break;
                        case 4:
                            render_app(&app, model_sit, model_shadow);
                            break;
                        case 5:
                            render_app(&app, model_sit_stand, model_shadow);
                            break;
                        case 6:
                            render_app(&app, model_sit_look, model_shadow);
                            break;
                        case 7:
                            render_app(&app, model_stand_yawn, model_shadow);
                            break;

                        default:
                            break;
                        }
                    }
                }
                destroy_app(&app);
                Mix_HaltChannel(-1);
                Mix_PlayMusic(sunset, -1);

                selected = 0;
                cat = 1;
            }

            if (cat == 1 && selected == 1)
            {
                running = 1;
            }
        }
        // Display updates on screen
        redraw(renderer);
    }

    // Free memory vagy mi
    Mix_FreeMusic(rest);
    Mix_FreeMusic(rain_bird);
    Mix_FreeMusic(garden);
    Mix_FreeMusic(soup);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
