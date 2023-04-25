#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    Model cube;
    Model rat;
    Material material;
    
    GLuint texture_id;
    GLuint texture_id2;
    GLuint texture_id3;
    GLfloat angle;
    GLfloat angle2;
    GLfloat light;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

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
void set_lighting(float x, float y, float z, float ambient_x, float ambient_y, float ambient_z);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

void rotate_cube(Scene *scene, float angle, float angle2);

#endif /* SCENE_H */
