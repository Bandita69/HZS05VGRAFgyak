#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene *scene)
{
    load_model(&(scene->cube), "assets/models/cat.obj");
    scene->texture_id = load_texture("assets/textures/cat.jpg");

    // load_model(&(scene->rat), "assets/models/rat.obj");
    // scene->texture_id2 = load_texture("assets/textures/rat.png");

    load_model(&(scene->rat), "assets/models/cube2.obj");
    scene->texture_id2 = load_texture("assets/textures/cube_2.jpg");
    scene->texture_id3 = load_texture("assets/textures/cube_22.jpg");

    scene->angle = 0.0;
    scene->angle2 = 0.0;
    scene->light = 1.0;

    // http://devernay.free.fr/cours/opengl/materials.html
    //  silver

    scene->material.ambient.red = 0.19225;
    scene->material.ambient.green = 0.19225;
    scene->material.ambient.blue = 0.19225;

    scene->material.diffuse.red = 0.50754;
    scene->material.diffuse.green = 0.50754;
    scene->material.diffuse.blue = 0.50754;

    scene->material.specular.red = 0.508273;
    scene->material.specular.green = 0.508273;
    scene->material.specular.blue = 0.508273;

    scene->material.shininess = 0.4 * 128.0;

    // alap
    // scene->material.ambient.red = 1.0;
    // scene->material.ambient.green = 1.0;
    // scene->material.ambient.blue = 1.0;

    // scene->material.diffuse.red = 1.0;
    // scene->material.diffuse.green = 1.0;
    // scene->material.diffuse.blue = 1.0;

    // scene->material.specular.red = 0.0;
    // scene->material.specular.green = 0.0;
    // scene->material.specular.blue = 0.0;

    // scene->material.shininess = 50.0;
}

void set_lighting(float x, float y, float z, float ambient_x, float ambient_y, float ambient_z)
{
    float ambient_light[] = {ambient_x, ambient_y, ambient_z, 1.0f};
    float diffuse_light[] = {1.0f, 1.0f, 1.0, 1.0f};
    float specular_light[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float position[] = {x, y, z, 1.0f};

    // stronger light
    //  float ambient_light[] = {0.2f, 0.2f, 0.2f, 1.0f};
    //  float diffuse_light[] = {0.8f, 0.8f, 0.8, 1.0f};
    //  float specular_light[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
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

void render_scene(const Scene *scene)
{

    set_material(&(scene->material));

    draw_origin();
    glBindTexture(GL_TEXTURE_2D, scene->texture_id);
    draw_model(&(scene->cube));
    // move second cube to the right
    glTranslatef(0.5, 0.5, 0.5);
    // rotate second cube
    glRotatef(scene->angle, 0.0, 1.0, 0.0);
    glRotatef(scene->angle2, 1.0, 0.0, 0.0);
    if (scene->light == 1.0)
    {
        set_lighting((scene->angle) / 5.0, (scene->angle2) / 5.0, 10.0, 0.0f, 0.0f, 0.0f);
        glBindTexture(GL_TEXTURE_2D, scene->texture_id2);
    }
    else
    {
        set_lighting((scene->angle) / 5.0, (scene->angle2) / 5.0, 10.0, 0.4f, 0.4f, 0.4f);
        glBindTexture(GL_TEXTURE_2D, scene->texture_id3);
    }

    draw_model(&(scene->rat));
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
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    // 4x4 rács rajzolása

    glColor3f(0, 0, 0);

    for (int i = 0; i < 4; i++)
    {
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
