#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include <stdio.h>
#include <math.h>

typedef struct Scene
{
    int dummy;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Update the scene.
 */
void update_scene(Scene* scene);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene, int toggle);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin(int toggle);

#endif /* SCENE_H */
