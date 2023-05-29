#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "model.h"
#include <SDL.h>

typedef struct Scene
{
    Model menu;
    GLuint menu_texture;

    Model table;
    GLuint table_texture;

    Model white_pieces[16];
    float white_coordinates[16][3];
    GLuint white_texture;

    Model black_pieces[16];
    float black_coordinates[16][3];
    GLuint black_texture;

    Material material;

    float light_sensitivity;

    bool is_menu_open; //This variable tells whether the menu is open or not

    bool f1, f2, f3, f4;
    
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(const float light);

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
void render_scene(const Scene* scene, SDL_Window* window);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

/**
 * Draw menu
*/
void draw_menu();

void init_coordinates(Scene* scene);

void ruy_lopez(Scene* scene, SDL_Window* window);

void default_table(const Scene* scene);

#endif /* SCENE_H */
