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
    //vec3 white_positions[16]; //a float tömb helyett lehetne használni
    float white_coordinates[16][3];
    GLuint white_texture;

    Model black_pieces[16];
    //vec3 black_positions[16]; //a float tömb helyett lehetne használni
    float black_coordinates[16][3];
    GLuint black_texture;

    Material material;

    float light_sensitivity;

    bool is_menu_open; //This variable tells whether the menu is open or not

    bool f1, f2, f3, f4;

    bool animation_is_on;
    
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

void draw_table(const Scene* scene);

void ruy_lopez(Scene* scene, SDL_Window* window);

void sicilian(Scene* scene, SDL_Window* window);

void scandinavian(Scene* scene, SDL_Window* window);

void london(Scene* scene, SDL_Window* window);

#endif /* SCENE_H */
