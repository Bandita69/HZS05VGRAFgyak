#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    Model cube;
    Model rat;

    float light_x;
    float light_y;
    float light_z;
    float light_angle;
    float diff_r;
    float diff_g;
    float diff_b;

    //shadow
    float shadow_x;
    float shadow_y;
    float shadow_z;
    float shadow_angle; // y-on forog
    GLuint shadow_texture;

    char * shadow_texture_path;

    char *stand;
    char *look;
    char *sit;
    char *sitting;
    char *standing;
    char *look_sit;
    char *yawn;

    Model shadow;

    Model background;
    Material material;
    Material material2;
    int frame;
    int end_frame;

    int frame_draw;
    int animate;
    int loaded;

    GLuint texture_id;
    GLuint texture_id2;
    GLuint texture_id3;
    GLuint texture_background;
    GLfloat angle;
    GLfloat angle2;
    GLfloat light;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene *scene, char *model_texture_path, char *background_texture_path, Model *model_rats, Model *model_look, Model *model_stand_sit, Model *model_sit, Model *model_sit_stand, Model *model_sit_look, Model *model_stand_yawn, Model * model_shadow);

/**
 * Set the lighting of the scene STRONK.
 */

void set_strong_light();

/**
 * Set the lighting of the scene. toggle
 */
void set_light(Scene *scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(float x, float y, float z, float diff_r, float diff_g, float diff_b);

/**
 * Set the current material.
 */
void set_material(const Material *material);

/**
 * Update the scene.
 */
void update_scene(Scene *scene);

/**
 * Render the scene objects.
 */
void render_scene(const Scene *scene, Model *model_rats, Model * model_shadows);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

void rotate_cube(Scene *scene, float angle, float angle2);

void draw_background();

void draw_background_sphere(const Scene *scene);

#endif /* SCENE_H */
