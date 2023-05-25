#include "scene.h"
#include <math.h>

#include <obj/load.h>
#include <obj/draw.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string.h>

void init_scene(Scene *scene, char *model_texture_path, char *background_texture_path, Model *model_rats, Model *model_look, Model *model_stand_sit, Model *model_sit, Model *model_sit_stand, Model *model_sit_look, Model *model_stand_yawn, Model *model_shadows)
{

    scene->texture_id2 = load_texture(model_texture_path);
    scene->texture_background = load_texture(background_texture_path);
    scene->shadow_texture = load_texture(scene->shadow_texture_path);

    char fileName[10000] = ""; // ezt egészen biztosan igy kell lefoglalni

    // betöltés ha üres a modell

    if (!(scene->loaded))
    {

        while (scene->frame <= scene->end_frame)
        {

            sprintf(fileName, scene->stand, scene->frame);
            load_model(&(scene->rat), fileName);

            model_rats[scene->frame] = scene->rat;

            scene->frame++;
        }

        scene->frame = 0;
        free_model(&(scene->rat));

        while (scene->frame <= scene->end_frame)
        {

            sprintf(fileName, scene->look, scene->frame);
            load_model(&(scene->rat), fileName);

            model_look[scene->frame] = scene->rat;

            scene->frame++;
        }

        scene->frame = 0;
        free_model(&(scene->rat));

        while (scene->frame <= scene->end_frame)
        {

            sprintf(fileName, scene->sit, scene->frame);
            load_model(&(scene->rat), fileName);

            model_stand_sit[scene->frame] = scene->rat;

            scene->frame++;
        }

        scene->frame = 0;
        free_model(&(scene->rat));

        while (scene->frame <= scene->end_frame)
        {

            sprintf(fileName, scene->sitting, scene->frame);
            load_model(&(scene->rat), fileName);

            model_sit[scene->frame] = scene->rat;

            scene->frame++;
        }

        scene->frame = 0;
        free_model(&(scene->rat));

        while (scene->frame <= scene->end_frame)
        {

            sprintf(fileName, scene->standing, scene->frame);
            load_model(&(scene->rat), fileName);

            model_sit_stand[scene->frame] = scene->rat;

            scene->frame++;
        }

        scene->frame = 0;
        free_model(&(scene->rat));

        while (scene->frame <= scene->end_frame)
        {

            sprintf(fileName, scene->look_sit, scene->frame);
            load_model(&(scene->rat), fileName);

            model_sit_look[scene->frame] = scene->rat;

            scene->frame++;
        }
        scene->frame = 0;
        free_model(&(scene->rat));

        while (scene->frame <= scene->end_frame)
        {

            sprintf(fileName, scene->yawn, scene->frame);
            load_model(&(scene->rat), fileName);

            model_stand_yawn[scene->frame] = scene->rat;

            scene->frame++;
        }
        scene->frame = 0;
        free_model(&(scene->rat));

        load_model(&(scene->shadow), "assets/models/cat_shadow_1.obj");
        model_shadows[1] = scene->shadow;
        load_model(&(scene->shadow), "assets/models/cat_shadow_2.obj");
        model_shadows[2] = scene->shadow;
        load_model(&(scene->shadow), "assets/models/cat_shadow_3.obj");
        model_shadows[3] = scene->shadow;
        load_model(&(scene->shadow), "assets/models/cat_shadow_4.obj");
        model_shadows[4] = scene->shadow;
        load_model(&(scene->shadow), "assets/models/cat_shadow_5.obj");
        model_shadows[5] = scene->shadow;

        free_model(&(scene->shadow));

        load_model(&(scene->background), "assets/models/sphere.obj");

        scene->loaded = 1;
    }

    scene->angle = 0.0;
    scene->angle2 = 0.0;
    scene->light = 1.0;

    // alap
    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;
}

void set_lighting(float x, float y, float z, float diff_r, float diff_g, float diff_b)
{
    glNormal3f(1, 1, 1);
    float ambient_light[] = {0.2f, 0.2f, 0.2f, 1.0f};
    float diffuse_light[] = {diff_r, diff_g, diff_b, 1.0f};
    float specular_light[] = {0.1f, 0.1f, 0.1f, 1.0f};
    float position[] = {x, y, z, 1.0f};

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
}

void set_material(const Material *material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue};

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue};

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene *scene)
{
}

void render_scene(const Scene *scene, Model *model_frames, Model * model_shadows)
{

    // draw_origin();

    // glColor3f(1.0, 1.0, 1.0);
    glNormal3f(1, 1, 1);

    set_material(&(scene->material));

    set_lighting(scene->light_x, scene->light_y, scene->light_z, scene->diff_r / 255.0f, scene->diff_g / 255.0f, scene->diff_b / 255.0f); // 255.0f / 255.0f, 228.0f / 255.0f, 206.0f / 255.0f)noon  RGB(255.0f / 255.0f, 100.0f / 255.0f, 50.0f / 255.0f) sunset

    // background
    glPushMatrix();
    glTranslatef(0.5, 0.5, 0.5);
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(-10, 0.0, 0.0, 1.0);
    glScalef(7.0, 7.0, 7.0);

    glBindTexture(GL_TEXTURE_2D, scene->texture_background);
    draw_model(&(scene->background));
    glPopMatrix();

    // shadow
    glPushMatrix();
    // átlátszó cuccok enable
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glTranslatef(0.5, 0.5, 0.5);
    glScalef(7.0, 7.0, 7.0);

    glBindTexture(GL_TEXTURE_2D, scene->shadow_texture);
    glRotatef(scene->shadow_angle, 0.0, 1.0, 0.0);
    // 0.5 átlátszó
    glColor4f(0.0, 0.0, 0.0, 0.5);

    draw_model(&(model_shadows[(int)((scene->light_angle +20) / 180 * 5)]));
    glPopMatrix();

    // cat
    glPushMatrix();
    // nem átlátszó
    glColor4f(1.0, 1.0, 1.0, 1.0);

    glTranslatef(0.5, 0.5, 0.5);
    glRotatef(90, 1.0, 0.0, 0.0);

    glBindTexture(GL_TEXTURE_2D, scene->texture_id2);

    draw_model(&model_frames[scene->frame_draw]);

    glPopMatrix();
}

void rotate_cube(Scene *scene, float angle, float angle2)
{
    // https://www.youtube.com/watch?v=3X-iqFRGqbc
    scene->angle += angle;
    scene->angle2 += angle2;
}

void set_light(Scene *scene)
{
    scene->light *= -1;
}

void draw_origin()
{

    glNormal3f(1, 1, 1);
    glBegin(GL_LINES);

    // 4x4 rács rajzolása

    for (int i = 0; i < 4; i++)
    {
        glColor3f(1.0, 1.0, 1.0);
        for (int j = 0; j < 4; j++)
        {

            glVertex3f(i / 4.0, j / 4.0, 0);
            glVertex3f((i + 1) / 4.0, j / 4.0, 0);
            glVertex3f((i + 1) / 4.0, j / 4.0, 0);
            glVertex3f((i + 1) / 4.0, (j + 1) / 4.0, 0);
            glVertex3f((i + 1) / 4.0, (j + 1) / 4.0, 0);

            glVertex3f(i / 4.0, (j + 1) / 4.0, 0);
            glVertex3f(i / 4.0, (j + 1) / 4.0, 0);
            glVertex3f(i / 4.0, j / 4.0, 0);

            glVertex3f(i / 4.0, 0, j / 4.0);
            glVertex3f((i + 1) / 4.0, 0, j / 4.0);
            glVertex3f((i + 1) / 4.0, 0, j / 4.0);
            glVertex3f((i + 1) / 4.0, 0, (j + 1) / 4.0);
            glVertex3f((i + 1) / 4.0, 0, (j + 1) / 4.0);

            glVertex3f(i / 4.0, 0, (j + 1) / 4.0);
            glVertex3f(i / 4.0, 0, (j + 1) / 4.0);
            glVertex3f(i / 4.0, 0, j / 4.0);

            glVertex3f(0, i / 4.0, j / 4.0);
            glVertex3f(0, (i + 1) / 4.0, j / 4.0);
            glVertex3f(0, (i + 1) / 4.0, j / 4.0);
            glVertex3f(0, (i + 1) / 4.0, (j + 1) / 4.0);
            glVertex3f(0, (i + 1) / 4.0, (j + 1) / 4.0);

            glVertex3f(0, i / 4.0, (j + 1) / 4.0);
            glVertex3f(0, i / 4.0, (j + 1) / 4.0);
            glVertex3f(0, i / 4.0, j / 4.0);
        }
    }

    glEnd();
}

// static background TODO: WIP

void draw_background()
{
    glNormal3f(1, 1, 1); // ez nem tudom miért kell
    glBindTexture(GL_TEXTURE_2D, 0);
    // valamit ez csinál
    glBegin(GL_QUADS);
    glPushMatrix();

    // light blue background
    glColor3f(0.0, 1.0, 1.0);

    glVertex3f(-2.0f, -2.0f, -2.0f);

    glVertex3f(2.0f, -2.0f, -2.0f);

    glVertex3f(2.0f, 2.0f, -2.0f);

    glVertex3f(-2.0f, 2.0f, -2.0f);
    glPopMatrix();
    glEnd();
}

// sphere background

void draw_background_sphere(const Scene *scene) // TODO: emiatt nem működik az animáció
{
    glNormal3f(1, 1, 1); // ez nem tudom miért kell
    glBindTexture(GL_TEXTURE_2D, scene->texture_id2);

    // light blue background
    glColor3f(0.0, 1.0, 1.0);

    int size = 5;

    // ez a függvény egy mandarint rajzol

    glBegin(GL_TRIANGLE_STRIP);

    for (int i = 0; i < 360; i += 10)
    {
        for (int j = 0; j < 360; j += 10)
        {
            glVertex3f(cos(i * M_PI / 180) * sin(j * M_PI / 180) * size, sin(i * M_PI / 180) * sin(j * M_PI / 180) * size, cos(j * M_PI / 180) * size);
            glVertex3f(cos(i * M_PI / 180) * sin((j + 10) * M_PI / 180) * size, sin(i * M_PI / 180) * sin((j + 10) * M_PI / 180) * size, cos((j + 10) * M_PI / 180) * size);
            glVertex3f(cos((i + 10) * M_PI / 180) * sin(j * M_PI / 180) * size, sin((i + 10) * M_PI / 180) * sin(j * M_PI / 180) * size, cos(j * M_PI / 180) * size);
            glVertex3f(cos((i + 10) * M_PI / 180) * sin((j + 10) * M_PI / 180) * size, sin((i + 10) * M_PI / 180) * sin((j + 10) * M_PI / 180) * size, cos((j + 10) * M_PI / 180) * size);
        }
    }

    glBindTexture(GL_TEXTURE_2D, scene->texture_id2);

    glEnd();
}
