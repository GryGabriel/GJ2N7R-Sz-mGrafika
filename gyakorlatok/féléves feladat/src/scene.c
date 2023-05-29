#include "scene.h"

#include <load.h>
#include <draw.h>
#include <stdio.h>
#include<unistd.h>
#include <SDL.h>

void init_scene(Scene* scene)
{
    //Load menu
    load_model(&(scene->menu), "assets/models/wall.obj");

    //Load the chess board
    load_model(&(scene->table), "assets/models/Table.obj");

    //Load white pieces
    for(int i=0;i<8;i++){
            load_model(&(scene->white_pieces[i]), "assets/models/Pawn.obj");
    }
    load_model(&(scene->white_pieces[8]), "assets/models/Rook.obj");
    load_model(&(scene->white_pieces[9]), "assets/models/Knight.obj");
    load_model(&(scene->white_pieces[10]), "assets/models/Bishop.obj");
    load_model(&(scene->white_pieces[11]), "assets/models/Queen.obj");
    load_model(&(scene->white_pieces[12]), "assets/models/King.obj");
    load_model(&(scene->white_pieces[13]), "assets/models/Bishop.obj");
    load_model(&(scene->white_pieces[14]), "assets/models/Knight.obj");
    load_model(&(scene->white_pieces[15]), "assets/models/Rook.obj");

    //Load black pieces
    for(int i=0;i<8;i++){
            load_model(&(scene->black_pieces[i]), "assets/models/Pawn.obj");
    }
    load_model(&(scene->black_pieces[8]), "assets/models/Rook.obj");
    load_model(&(scene->black_pieces[9]), "assets/models/Knight.obj");
    load_model(&(scene->black_pieces[10]), "assets/models/Bishop.obj");
    load_model(&(scene->black_pieces[11]), "assets/models/Queen.obj");
    load_model(&(scene->black_pieces[12]), "assets/models/King.obj");
    load_model(&(scene->black_pieces[13]), "assets/models/Bishop.obj");
    load_model(&(scene->black_pieces[14]), "assets/models/Knight.obj");
    load_model(&(scene->black_pieces[15]), "assets/models/Rook.obj");


    scene->table_texture = load_texture("assets/textures/Table.jpg");
    scene->white_texture = load_texture("assets/textures/White.jpg");
    scene->black_texture = load_texture("assets/textures/Black.jpg");
    scene->menu_texture = load_texture("assets/textures/menu.png");


    scene->material.ambient.red = 1;
    scene->material.ambient.green = 1;
    scene->material.ambient.blue = 1;

    scene->material.diffuse.red = 1;
    scene->material.diffuse.green = 0.5;
    scene->material.diffuse.blue = 0.25;

    scene->material.specular.red = 0.25;
    scene->material.specular.green = 0.5;
    scene->material.specular.blue = 1;

    scene->material.shininess = 0.8;

    scene->light_sensitivity = 1.0;

    init_coordinates(scene);

    scene->f1 = false;
    scene->f2 = false;
    scene->f3 = false;
    scene->f4 = false;
}

void set_lighting(const float light)
{
    float ambient_light[] = { light, light, light, light };
    float diffuse_light[] = { light, light, light, light };
    float specular_light[] = { light, light, light, light };
    float position[] = { 0.0f, 0.0f, 0.0f, 0.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene)
{
}

void render_scene(const Scene* scene, SDL_Window* window)
{
    if(scene->f1){
        ruy_lopez(scene, window);
    }else{
        default_table(scene);
    }
}

void ruy_lopez(Scene* scene, SDL_Window* window){
    float initialX = 88.0f;
    float targetX = 107.5f;
    float stepSize = 6.5f;
    float currentPositionX = initialX;

    while (currentPositionX < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->table_texture);
        glRotatef(90, 1, 0, 0);
        glScalef(0.1f, 0.1f, 0.1f);
        glTranslatef(40, 0, 0);
        glRotatef(180, 0, 1, 0);
        draw_model(&(scene->table));
        glPopMatrix();

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(currentPositionX, -1.0f, -45.0f);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[4]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        currentPositionX += stepSize;

        SDL_Delay(1000);
    }
    scene->f1 = false;
}

void default_table(const Scene* scene){
    set_material(&(scene->material));
    set_lighting(scene->light_sensitivity);

    //If is_menu_on is true, draw the menu
    if(scene->is_menu_open){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->menu_texture);
        glScalef(4.0f, 4.0f, 4.0f);
        glRotatef(180, 1, 0, 0);
        glTranslatef(1.5, -1.5, -0.5);
        glRotatef(90, 1, 0, 0);
        glRotatef(45, 0, 1, 0);
        // Define the rectangle vertices and texture coordinates
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f, -0.5f); // Bottom-left vertex
        glTexCoord2f(1.0f, 0.0f); glVertex2f(0.5f, -0.5f);  // Bottom-right vertex
        glTexCoord2f(1.0f, 1.0f); glVertex2f(0.5f, 0.5f);   // Top-right vertex
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.5f, 0.5f);  // Top-left vertex
        glEnd();
        glPopMatrix();
    }

    //Draw table
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->table_texture);
    glRotatef(90, 1, 0, 0);
    glScalef(0.1f, 0.1f, 0.1f);
    glTranslatef(40, 0, 0);
    glRotatef(180, 0, 1, 0);
    draw_model(&(scene->table));
    glPopMatrix();

    //Draw white pieces
    for(int i=0;i<16;i++){
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[i][0], scene->white_coordinates[i][1], scene->white_coordinates[i][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[i]));
        glPopMatrix();
    }
    //Draw black pieces
    for(int i=0;i<16;i++){
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[i][0], scene->black_coordinates[i][1], scene->black_coordinates[i][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[i]));
        glPopMatrix();
    }
}

//Initialize pieces' coordinates
void init_coordinates(Scene* scene){
    /* White pieces */
    //Pawns
        scene->white_coordinates[0][0] = 88;
        scene->white_coordinates[0][1] = -1;
        scene->white_coordinates[0][2] = -63;


        scene->white_coordinates[1][0] = 88;
        scene->white_coordinates[1][1] = -1;
        scene->white_coordinates[1][2] = -45;
        

        scene->white_coordinates[2][0] = 88;
        scene->white_coordinates[2][1] = -1;
        scene->white_coordinates[2][2] = -27;
        

        scene->white_coordinates[3][0] = 88;
        scene->white_coordinates[3][1] = -1;
        scene->white_coordinates[3][2] = -9;
        

        scene->white_coordinates[4][0] = 88;
        scene->white_coordinates[4][1] = -1;
        scene->white_coordinates[4][2] = 9;
        

        scene->white_coordinates[5][0] = 88;
        scene->white_coordinates[5][1] = -1;
        scene->white_coordinates[5][2] = 27;
        

        scene->white_coordinates[6][0] = 88;
        scene->white_coordinates[6][1] = -1;
        scene->white_coordinates[6][2] = 45;
        

        scene->white_coordinates[7][0] = 88;
        scene->white_coordinates[7][1] = -1;
        scene->white_coordinates[7][2] = 63;
    
    //Left rook
    scene->white_coordinates[8][0] = 70;
    scene->white_coordinates[8][1] = -1;
    scene->white_coordinates[8][2] = -63;
    
    //Left knight
    scene->white_coordinates[9][0] = 70;
    scene->white_coordinates[9][1] = -1;
    scene->white_coordinates[9][2] = -45;
    
    //Left bishop
    scene->white_coordinates[10][0] = 70;
    scene->white_coordinates[10][1] = -1;
    scene->white_coordinates[10][2] = -27;
    
    //Queen
    scene->white_coordinates[11][0] = 70;
    scene->white_coordinates[11][1] = -1;
    scene->white_coordinates[11][2] = -9;
    
    //King
    scene->white_coordinates[12][0] = 70;
    scene->white_coordinates[12][1] = -1;
    scene->white_coordinates[12][2] = 9;
    
    //Right bishop
    scene->white_coordinates[13][0] = 70;
    scene->white_coordinates[13][1] = -1;
    scene->white_coordinates[13][2] = 27;
    
    //Right knight
    scene->white_coordinates[14][0] = 70;
    scene->white_coordinates[14][1] = -1;
    scene->white_coordinates[14][2] = 45;
    
    //Right rook
    scene->white_coordinates[15][0] = 70;
    scene->white_coordinates[15][1] = -1;
    scene->white_coordinates[15][2] = 63;

    /* Black pieces */
    //Pawns
        scene->black_coordinates[0][0] = 178;
        scene->black_coordinates[0][1] = -1;
        scene->black_coordinates[0][2] = -63;

        scene->black_coordinates[1][0] = 178;
        scene->black_coordinates[1][1] = -1;
        scene->black_coordinates[1][2] = -45;

        scene->black_coordinates[2][0] = 178;
        scene->black_coordinates[2][1] = -1;
        scene->black_coordinates[2][2] = -27;

        scene->black_coordinates[3][0] = 178;
        scene->black_coordinates[3][1] = -1;
        scene->black_coordinates[3][2] = -9;

        scene->black_coordinates[4][0] = 178;
        scene->black_coordinates[4][1] = -1;
        scene->black_coordinates[4][2] = 9;

        scene->black_coordinates[5][0] = 178;
        scene->black_coordinates[5][1] = -1;
        scene->black_coordinates[5][2] = 27;

        scene->black_coordinates[6][0] = 178;
        scene->black_coordinates[6][1] = -1;
        scene->black_coordinates[6][2] = 45;

        scene->black_coordinates[7][0] = 178;
        scene->black_coordinates[7][1] = -1;
        scene->black_coordinates[7][2] = 63;

    //Left Rook
    scene->black_coordinates[8][0] = 197;
    scene->black_coordinates[8][1] = -1;
    scene->black_coordinates[8][2] = -63;

    //Left knight
    scene->black_coordinates[9][0] = 197;
    scene->black_coordinates[9][1] = -1;
    scene->black_coordinates[9][2] = -45;

    //Left bishop
    scene->black_coordinates[10][0] = 197;
    scene->black_coordinates[10][1] = -1;
    scene->black_coordinates[10][2] = -27;

    //King
    scene->black_coordinates[11][0] = 197;
    scene->black_coordinates[11][1] = -1;
    scene->black_coordinates[11][2] = -9;

    //Queen
    scene->black_coordinates[12][0] = 197;
    scene->black_coordinates[12][1] = -1;
    scene->black_coordinates[12][2] = 9;

    //Right bishop
    scene->black_coordinates[13][0] = 197;
    scene->black_coordinates[13][1] = -1;
    scene->black_coordinates[13][2] = 27;

    //Right knight
    scene->black_coordinates[14][0] = 197;
    scene->black_coordinates[14][1] = -1;
    scene->black_coordinates[14][2] = 45;

    //Right rook
    scene->black_coordinates[15][0] = 197;
    scene->black_coordinates[15][1] = -1;
    scene->black_coordinates[15][2] = 63;
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

    glEnd();
}
