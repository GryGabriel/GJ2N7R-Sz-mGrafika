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
    }else if(scene->f2){
        sicilian(scene, window);
    }else if(scene->f3){
        scandinavian(scene, window);
    }else if(scene->f4){
        london(scene, window);
    }else{
        draw_table(scene);
    }
}

void draw_table(const Scene* scene){
    set_material(&(scene->material));
    set_lighting(scene->light_sensitivity);

    //If is_menu_on is true, draw the menu
    if(scene->is_menu_open){
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->menu_texture);
        glScalef(6.0f, 6.0f, 6.0f);
        glRotatef(180, 1, 0, 0);
        glTranslatef(1.2, 0, -0.5);
        glRotatef(90, 1, 0, 0);
        glRotatef(90, 0, 1, 0);
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
    glTranslatef(40, -16, 0);
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
        scene->white_coordinates[0][1] = -55;
        scene->white_coordinates[0][2] = -63;


        scene->white_coordinates[1][0] = 88;
        scene->white_coordinates[1][1] = -55;
        scene->white_coordinates[1][2] = -45;
        

        scene->white_coordinates[2][0] = 88;
        scene->white_coordinates[2][1] = -55;
        scene->white_coordinates[2][2] = -27;
        

        scene->white_coordinates[3][0] = 88;
        scene->white_coordinates[3][1] = -55;
        scene->white_coordinates[3][2] = -9;
        

        scene->white_coordinates[4][0] = 88;
        scene->white_coordinates[4][1] = -55;
        scene->white_coordinates[4][2] = 9;
        

        scene->white_coordinates[5][0] = 88;
        scene->white_coordinates[5][1] = -55;
        scene->white_coordinates[5][2] = 27;
        

        scene->white_coordinates[6][0] = 88;
        scene->white_coordinates[6][1] = -55;
        scene->white_coordinates[6][2] = 45;
        

        scene->white_coordinates[7][0] = 88;
        scene->white_coordinates[7][1] = -55;
        scene->white_coordinates[7][2] = 63;
    
    //Left rook
    scene->white_coordinates[8][0] = 70;
    scene->white_coordinates[8][1] = -55;
    scene->white_coordinates[8][2] = -63;
    
    //Left knight
    scene->white_coordinates[9][0] = 70;
    scene->white_coordinates[9][1] = -55;
    scene->white_coordinates[9][2] = -45;
    
    //Left bishop
    scene->white_coordinates[10][0] = 70;
    scene->white_coordinates[10][1] = -55;
    scene->white_coordinates[10][2] = -27;
    
    //Queen
    scene->white_coordinates[11][0] = 70;
    scene->white_coordinates[11][1] = -55;
    scene->white_coordinates[11][2] = -9;
    
    //King
    scene->white_coordinates[12][0] = 70;
    scene->white_coordinates[12][1] = -55;
    scene->white_coordinates[12][2] = 9;
    
    //Right bishop
    scene->white_coordinates[13][0] = 70;
    scene->white_coordinates[13][1] = -55;
    scene->white_coordinates[13][2] = 27;
    
    //Right knight
    scene->white_coordinates[14][0] = 70;
    scene->white_coordinates[14][1] = -55;
    scene->white_coordinates[14][2] = 45;
    
    //Right rook
    scene->white_coordinates[15][0] = 70;
    scene->white_coordinates[15][1] = -55;
    scene->white_coordinates[15][2] = 63;

    /* Black pieces */
    //Pawns
        scene->black_coordinates[0][0] = 178;
        scene->black_coordinates[0][1] = -55;
        scene->black_coordinates[0][2] = -63;

        scene->black_coordinates[1][0] = 178;
        scene->black_coordinates[1][1] = -55;
        scene->black_coordinates[1][2] = -45;

        scene->black_coordinates[2][0] = 178;
        scene->black_coordinates[2][1] = -55;
        scene->black_coordinates[2][2] = -27;

        scene->black_coordinates[3][0] = 178;
        scene->black_coordinates[3][1] = -55;
        scene->black_coordinates[3][2] = -9;

        scene->black_coordinates[4][0] = 178;
        scene->black_coordinates[4][1] = -55;
        scene->black_coordinates[4][2] = 9;

        scene->black_coordinates[5][0] = 178;
        scene->black_coordinates[5][1] = -55;
        scene->black_coordinates[5][2] = 27;

        scene->black_coordinates[6][0] = 178;
        scene->black_coordinates[6][1] = -55;
        scene->black_coordinates[6][2] = 45;

        scene->black_coordinates[7][0] = 178;
        scene->black_coordinates[7][1] = -55;
        scene->black_coordinates[7][2] = 63;

    //Left Rook
    scene->black_coordinates[8][0] = 197;
    scene->black_coordinates[8][1] = -55;
    scene->black_coordinates[8][2] = -63;

    //Left knight
    scene->black_coordinates[9][0] = 197;
    scene->black_coordinates[9][1] = -55;
    scene->black_coordinates[9][2] = -45;

    //Left bishop
    scene->black_coordinates[10][0] = 197;
    scene->black_coordinates[10][1] = -55;
    scene->black_coordinates[10][2] = -27;

    //Queen
    scene->black_coordinates[11][0] = 197;
    scene->black_coordinates[11][1] = -55;
    scene->black_coordinates[11][2] = -9;

    //King
    scene->black_coordinates[12][0] = 197;
    scene->black_coordinates[12][1] = -55;
    scene->black_coordinates[12][2] = 9;

    //Right bishop
    scene->black_coordinates[13][0] = 197;
    scene->black_coordinates[13][1] = -55;
    scene->black_coordinates[13][2] = 27;

    //Right knight
    scene->black_coordinates[14][0] = 197;
    scene->black_coordinates[14][1] = -55;
    scene->black_coordinates[14][2] = 45;

    //Right rook
    scene->black_coordinates[15][0] = 197;
    scene->black_coordinates[15][1] = -55;
    scene->black_coordinates[15][2] = 63;

    scene->animation_is_on = false;
}

void ruy_lopez(Scene* scene, SDL_Window* window){
    float targetX;
    float targetY;
    float step_sizeX;
    float step_sizeY;
    
    /**
     * 1.e4
    */
    targetX = 124.0f; //From 88.0 to targetX
    step_sizeX = 1.0f;

    while (scene->white_coordinates[4][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[4][0], scene->white_coordinates[4][1], scene->white_coordinates[4][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[4]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[4][0] += step_sizeX;

    }

     /**
     * 1...e5
    */
    targetX = 142.0f; //From 178.0 to targetX
    step_sizeX = 1.0f;

    while (scene->black_coordinates[4][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[4][0], scene->black_coordinates[4][1], scene->black_coordinates[4][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[4]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[4][0] -= step_sizeX;

    }

    /**
     * 2.Nf3
    */
    targetX = 106.0f; //From 70.0 to targetX
    targetY = 27.0; //From 45 to targetY
    step_sizeX = 2.0f;
    step_sizeY = 1.0f;

    while (scene->white_coordinates[14][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[14][0], scene->white_coordinates[14][1], scene->white_coordinates[14][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[14]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[14][0] += step_sizeX;
        scene->white_coordinates[14][2] -= step_sizeY;

    }

     /**
     * 2...Nc6
    */
    targetX = 161.0f; //From 197.0 to targetX
    targetY = -27.0; //From -45.0 to targetY
    step_sizeX = 2.0f;
    step_sizeY = 1.0f;

    while (scene->black_coordinates[9][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[9][0], scene->black_coordinates[9][1], scene->black_coordinates[9][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[9]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[9][0] -= step_sizeX;
        scene->black_coordinates[9][2] += step_sizeY;

    }

    /**
     * 3.Bb5
    */
    targetX = 142.0f; //From 70.0 to targetX
    targetY = -45.0; //From 27 to targetY
    step_sizeX = 1.0f;
    step_sizeY = 1.0f;

    while (scene->white_coordinates[13][0] < targetX && scene->white_coordinates[13][3] > targetY) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[13][0], scene->white_coordinates[13][1], scene->white_coordinates[13][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[13]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[13][0] += step_sizeX;
        scene->white_coordinates[13][2] -= step_sizeY;

    }

    /**
     * 3...a6
    */
    targetX = 160.0f; //From 178.0
    step_sizeX = 1.0f;

    while (scene->black_coordinates[0][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[0][0], scene->black_coordinates[0][1], scene->black_coordinates[0][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[0]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[0][0] -= step_sizeX;

    }

     /**
     * 4.Ba4
    */
    targetX = 124.0f; //From 142.0 to targetX
    targetY = -63.0; //From -45 to targetY
    step_sizeX = 1.0f;
    step_sizeY = 1.0f;

    while (scene->white_coordinates[13][0] > targetX && scene->white_coordinates[13][3] > targetY) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[13][0], scene->white_coordinates[13][1], scene->white_coordinates[13][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[13]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[13][0] -= step_sizeX;
        scene->white_coordinates[13][2] -= step_sizeY;

    }

    /**
     * 4...Nf6
    */
    targetX = 161.0f; //From 197.0
    targetY = 27; //From 45
    step_sizeX = 2.0f;
    step_sizeY = 1.0f;

    while (scene->black_coordinates[14][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[14][0], scene->black_coordinates[14][1], scene->black_coordinates[14][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[14]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[14][0] -= step_sizeX;
        scene->black_coordinates[14][2] -= step_sizeY;

    }

    /**
     * 5.O-O
    */
    targetY = 45.0f; //From 9.0 to targetY - KING
    step_sizeY = 1.0f;

    while (scene->white_coordinates[12][2] < targetY) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the king at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[12][0], scene->white_coordinates[12][1], scene->white_coordinates[12][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[12]));
        glPopMatrix();

        // Draw the rook at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[15][0], scene->white_coordinates[15][1], scene->white_coordinates[15][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[15]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->white_coordinates[12][2] += step_sizeY;
        scene->white_coordinates[15][2] -= step_sizeY;

    }
    
    scene->f1 = false;
}

void sicilian(Scene* scene, SDL_Window* window){
    float targetX;
    float targetY;
    float step_sizeX;
    float step_sizeY;
    
    /**
     * 1.e4
    */
    targetX = 124.0f; //From 88.0 to targetX
    step_sizeX = 1.0f;

    while (scene->white_coordinates[4][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[4][0], scene->white_coordinates[4][1], scene->white_coordinates[4][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[4]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[4][0] += step_sizeX;

    }

    /**
     * 1...c5
    */
    targetX = 142.0f; //From 178.0 to targetX
    step_sizeX = 1.0f;

    while (scene->black_coordinates[2][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[2][0], scene->black_coordinates[2][1], scene->black_coordinates[2][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[2]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[2][0] -= step_sizeX;

    }

    /**
     * 2.Nf3
    */
    targetX = 106.0f; //From 70.0 to targetX
    targetY = 27.0; //From 45 to targetY
    step_sizeX = 2.0f;
    step_sizeY = 1.0f;

    while (scene->white_coordinates[14][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[14][0], scene->white_coordinates[14][1], scene->white_coordinates[14][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[14]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[14][0] += step_sizeX;
        scene->white_coordinates[14][2] -= step_sizeY;

    }

    /**
     * 2...d6
    */
    targetX = 160.0f; //From 178.0 to targetX
    step_sizeX = 1.0f;

    while (scene->black_coordinates[3][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[3][0], scene->black_coordinates[3][1], scene->black_coordinates[3][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[3]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[3][0] -= step_sizeX;

    }

    /**
     * 3.d4
    */
    targetX = 124.0f; //From 88.0 to targetX
    step_sizeX = 1.0f;

    while (scene->white_coordinates[3][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[3][0], scene->white_coordinates[3][1], scene->white_coordinates[3][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[3]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[3][0] += step_sizeX;

    }

    /**
     * 3...cxd6
    */
    targetX = 124.0f; //From 142.0 to targetX
    targetY = -9; //From -27
    step_sizeX = 1.0f;
    step_sizeY = 1.0f;

    while (scene->black_coordinates[2][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[2][0], scene->black_coordinates[2][1], scene->black_coordinates[2][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[2]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[2][0] -= step_sizeX;
        scene->black_coordinates[2][2] += step_sizeY;

    }
    scene->white_coordinates[3][2] = -100;

    /**
     * 4.Nxd4
    */
    targetX = 124.0f; //From 106.0 to targetX
    targetY = -9.0; //From 27 to targetY
    step_sizeX = 1.0f;
    step_sizeY = 2.0f;

    while (scene->white_coordinates[14][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[14][0], scene->white_coordinates[14][1], scene->white_coordinates[14][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[14]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[14][0] += step_sizeX;
        scene->white_coordinates[14][2] -= step_sizeY;

    }
    scene->black_coordinates[2][2] = 100;

    /**
     * 4...Nf6
    */
    targetX = 161.0f; //From 197.0
    targetY = 27; //From 45
    step_sizeX = 2.0f;
    step_sizeY = 1.0f;

    while (scene->black_coordinates[14][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[14][0], scene->black_coordinates[14][1], scene->black_coordinates[14][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[14]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[14][0] -= step_sizeX;
        scene->black_coordinates[14][2] -= step_sizeY;

    }

    /**
     * 5.Nc3
    */
    targetX = 106.0f; //From 70.0 to targetX
    targetY = -27.0; //From -45 to targetY
    step_sizeX = 2.0f;
    step_sizeY = 1.0f;

    while (scene->white_coordinates[9][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[9][0], scene->white_coordinates[9][1], scene->white_coordinates[9][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[9]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[9][0] += step_sizeX;
        scene->white_coordinates[9][2] += step_sizeY;

    }

    /**
     * 5...g6
    */
    targetX = 160.0f; //From 178.0 to targetX
    step_sizeX = 1.0f;

    while (scene->black_coordinates[6][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[6][0], scene->black_coordinates[6][1], scene->black_coordinates[6][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[6]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[6][0] -= step_sizeX;

    }

    scene->f2 = false;
}

void scandinavian(Scene* scene, SDL_Window* window){
    float targetX;
    float targetY;
    float step_sizeX;
    float step_sizeY;
    
    /**
     * 1.e4
    */
    targetX = 124.0f; //From 88.0 to targetX
    step_sizeX = 1.0f;

    while (scene->white_coordinates[4][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[4][0], scene->white_coordinates[4][1], scene->white_coordinates[4][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[4]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[4][0] += step_sizeX;

    }

    /**
     * 1...d5
    */
    targetX = 142.0f; //From 178.0 to targetX
    step_sizeX = 1.0f;

    while (scene->black_coordinates[3][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[3][0], scene->black_coordinates[3][1], scene->black_coordinates[3][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[3]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[3][0] -= step_sizeX;

    }

    /**
     * 2.exd5
    */
    targetX = 142.0f; //From 124.0 to targetX
    targetY = -9; //From 9.0 to targetY
    step_sizeX = 1.0f;
    step_sizeY = 1.0f;

    while (scene->white_coordinates[4][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[4][0], scene->white_coordinates[4][1], scene->white_coordinates[4][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[4]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[4][0] += step_sizeX;
        scene->white_coordinates[4][2] -= step_sizeY;

    }
    scene->black_coordinates[3][2] = 100;

    /**
     * 2...Qxd5
    */
    targetX = 143.0f; //From 197.0 to targetX
    step_sizeX = 1.0f;

    while (scene->black_coordinates[11][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[11][0], scene->black_coordinates[11][1], scene->black_coordinates[11][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[11]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[11][0] -= step_sizeX;

    }
    scene->white_coordinates[4][2] = -100;

    /**
     * 3.Nc3
    */
    targetX = 106.0f; //From 70.0 to targetX
    targetY = -27.0; //From -45 to targetY
    step_sizeX = 2.0f;
    step_sizeY = 1.0f;

    while (scene->white_coordinates[9][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[9][0], scene->white_coordinates[9][1], scene->white_coordinates[9][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[9]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[9][0] += step_sizeX;
        scene->white_coordinates[9][2] += step_sizeY;

    }

    /**
     * 3...Qd8
    */
    targetX = 197.0f; //From 143.0 to targetX
    step_sizeX = 1.0f;

    while (scene->black_coordinates[11][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[11][0], scene->black_coordinates[11][1], scene->black_coordinates[11][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[11]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[11][0] += step_sizeX;

    }

     /**
     * 4.d4
    */
    targetX = 124.0f; //From 88.0 to targetX
    step_sizeX = 1.0f;

    while (scene->white_coordinates[3][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[3][0], scene->white_coordinates[3][1], scene->white_coordinates[3][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[3]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[3][0] += step_sizeX;

    }

    /**
     * 4...Nf6
    */
    targetX = 161.0f; //From 197.0
    targetY = 27; //From 45
    step_sizeX = 2.0f;
    step_sizeY = 1.0f;

    while (scene->black_coordinates[14][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[14][0], scene->black_coordinates[14][1], scene->black_coordinates[14][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[14]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[14][0] -= step_sizeX;
        scene->black_coordinates[14][2] -= step_sizeY;

    }

    /**
     * 5.Qf3
    */
    targetX = 106.0f; //From 70.0 to targetX
    targetY = 27; //From -9
    step_sizeX = 1.0f;
    step_sizeY = 1.0f;

    while (scene->white_coordinates[11][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[11][0], scene->white_coordinates[11][1], scene->white_coordinates[11][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[11]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[11][0] += step_sizeX;
        scene->white_coordinates[11][2] += step_sizeY;

    }

    /**
     * 5...c3
    */
    targetX = 160.0f; //From 178.0 to targetX
    step_sizeX = 1.0f;

    while (scene->black_coordinates[2][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[2][0], scene->black_coordinates[2][1], scene->black_coordinates[2][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[2]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[2][0] -= step_sizeX;

    }

    scene->f3 = false;
}

void london(Scene* scene, SDL_Window* window){
    float targetX;
    float targetY;
    float step_sizeX;
    float step_sizeY;

    /**
     * 1.d4
    */
    targetX = 124.0f; //From 88.0 to targetX
    step_sizeX = 1.0f;

    while (scene->white_coordinates[3][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[3][0], scene->white_coordinates[3][1], scene->white_coordinates[3][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[3]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[3][0] += step_sizeX;

    }

    /**
     * 1...d5
    */
    targetX = 142.0f; //From 178.0 to targetX
    step_sizeX = 1.0f;

    while (scene->black_coordinates[3][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[3][0], scene->black_coordinates[3][1], scene->black_coordinates[3][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[3]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[3][0] -= step_sizeX;

    }

    /**
     * 2.Bf4
    */
    targetX = 124.0f; //From 70.0 to targetX
    targetY = 27.0; //From -27 to targetY
    step_sizeX = 1.0f;
    step_sizeY = 1.0f;

    while (scene->white_coordinates[10][0] < targetX && scene->white_coordinates[10][3] > targetY) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[10][0], scene->white_coordinates[10][1], scene->white_coordinates[10][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[10]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[10][0] += step_sizeX;
        scene->white_coordinates[10][2] += step_sizeY;

    }

    /**
     * 2...Nf6
    */
    targetX = 161.0f; //From 197.0
    targetY = 27; //From 45
    step_sizeX = 2.0f;
    step_sizeY = 1.0f;

    while (scene->black_coordinates[14][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[14][0], scene->black_coordinates[14][1], scene->black_coordinates[14][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[14]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[14][0] -= step_sizeX;
        scene->black_coordinates[14][2] -= step_sizeY;

    }

    /**
     * 3.e3
    */
    targetX = 106.0f; //From 88.0 to targetX
    step_sizeX = 1.0f;

    while (scene->white_coordinates[4][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[4][0], scene->white_coordinates[4][1], scene->white_coordinates[4][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[4]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[4][0] += step_sizeX;

    }

    /**
     * 3...c5
    */
    targetX = 142.0f; //From 178.0 to targetX
    step_sizeX = 1.0f;

    while (scene->black_coordinates[2][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[2][0], scene->black_coordinates[2][1], scene->black_coordinates[2][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[2]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[2][0] -= step_sizeX;

    }

    /**
     * 4.c3
    */
    targetX = 106.0f; //From 88.0 to targetX
    step_sizeX = 1.0f;

    while (scene->white_coordinates[2][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[2][0], scene->white_coordinates[2][1], scene->white_coordinates[2][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[2]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[2][0] += step_sizeX;

    }

    /**
     * 4...Nc6
    */
    targetX = 161.0f; //From 197.0 to targetX
    targetY = -27.0; //From -45.0 to targetY
    step_sizeX = 2.0f;
    step_sizeY = 1.0f;

    while (scene->black_coordinates[9][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[9][0], scene->black_coordinates[9][1], scene->black_coordinates[9][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[9]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[9][0] -= step_sizeX;
        scene->black_coordinates[9][2] += step_sizeY;

    }

    /**
     * 5.Nd2
    */
    targetX = 88.0f; //From 70.0 to targetX
    targetY = -9.0; //From -45 to targetY
    step_sizeX = 1.0f;
    step_sizeY = 2.0f;

    while (scene->white_coordinates[9][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[9][0], scene->white_coordinates[9][1], scene->white_coordinates[9][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[9]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[9][0] += step_sizeX;
        scene->white_coordinates[9][2] += step_sizeY;

    }

     /**
     * 5...e6
    */
    targetX = 160.0f; //From 178.0 to targetX
    step_sizeX = 1.0f;

    while (scene->black_coordinates[4][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[4][0], scene->black_coordinates[4][1], scene->black_coordinates[4][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[4]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[4][0] -= step_sizeX;

    }

    /**
     * 6.Nf3
    */
    targetX = 106.0f; //From 70.0 to targetX
    targetY = 27.0; //From 45 to targetY
    step_sizeX = 2.0f;
    step_sizeY = 1.0f;

    while (scene->white_coordinates[14][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[14][0], scene->white_coordinates[14][1], scene->white_coordinates[14][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[14]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[14][0] += step_sizeX;
        scene->white_coordinates[14][2] -= step_sizeY;

    }

    /**
     * 6...Bd6
    */
    targetX = 161.0f; //From 197.0 to targetX
    targetY = -9.0; //From 27 to targetY
    step_sizeX = 1.0f;
    step_sizeY = 1.0f;

    while (scene->black_coordinates[13][0] > targetX && scene->black_coordinates[13][3] > targetY) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[13][0], scene->black_coordinates[13][1], scene->black_coordinates[13][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[13]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->black_coordinates[13][0] -= step_sizeX;
        scene->black_coordinates[13][2] -= step_sizeY;

    }

    /**
     * 7.Bg3
    */
    targetX = 106.0f; //From 124.0 to targetX
    targetY = 45.0; //From 27 to targetY
    step_sizeX = 1.0f;
    step_sizeY = 1.0f;
    while (scene->white_coordinates[10][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[10][0], scene->white_coordinates[10][1], scene->white_coordinates[10][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[10]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[10][0] -= step_sizeX;
        scene->white_coordinates[10][2] += step_sizeY;

    }

    /**
     * 7...O-O
    */
    targetY = 45.0f; //From 9.0 to targetY - KING
    step_sizeY = 1.0f;

    while (scene->black_coordinates[12][2] < targetY) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the king at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[12][0], scene->black_coordinates[12][1], scene->black_coordinates[12][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[12]));
        glPopMatrix();

        // Draw the rook at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[15][0], scene->black_coordinates[15][1], scene->black_coordinates[15][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[15]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[12][2] += step_sizeY;
        scene->black_coordinates[15][2] -= step_sizeY;

    }

    /**
     * 8.Bd3
    */
    targetX = 106.0f; //From 70.0 to targetX
    targetY = -9.0; //From 27 to targetY
    step_sizeX = 1.0f;
    step_sizeY = 1.0f;

    while (scene->white_coordinates[13][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[13][0], scene->white_coordinates[13][1], scene->white_coordinates[13][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[13]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[13][0] += step_sizeX;
        scene->white_coordinates[13][2] -= step_sizeY;

    }

    /**
     * 8...b6
    */
    targetX = 160.0f; //From 178.0 to targetX
    step_sizeX = 1.0f;

    while (scene->black_coordinates[1][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[1][0], scene->black_coordinates[1][1], scene->black_coordinates[1][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[1]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);

        // Update the current position for the next iteration
        scene->black_coordinates[1][0] -= step_sizeX;

    }

     /**
     * 9.Qe2
    */
    targetX = 88.0f; //From 70.0 to targetX
    targetY = 9; //From -9
    step_sizeX = 1.0f;
    step_sizeY = 1.0f;

    while (scene->white_coordinates[11][0] < targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->white_coordinates[11][0], scene->white_coordinates[11][1], scene->white_coordinates[11][2]);
        glBindTexture(GL_TEXTURE_2D, scene->white_texture);
        draw_model(&(scene->white_pieces[11]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->white_coordinates[11][0] += step_sizeX;
        scene->white_coordinates[11][2] += step_sizeY;

    }

    /**
     * 9...Bb7
    */
    targetX = 179.0f; //From 197.0 to targetX
    targetY = -45.0; //From -27 to targetY
    step_sizeX = 1.0f;
    step_sizeY = 1.0f;

    while (scene->black_coordinates[10][0] > targetX) {
        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Draw the whole table
        draw_table(scene);

        // Draw the chess piece at the current position
        glPushMatrix();
        glRotatef(90, 1, 0, 0);
        glScalef(0.03f, 0.03f, 0.03f);
        glTranslatef(scene->black_coordinates[10][0], scene->black_coordinates[10][1], scene->black_coordinates[10][2]);
        glBindTexture(GL_TEXTURE_2D, scene->black_texture);
        draw_model(&(scene->black_pieces[10]));
        glPopMatrix();

        // Swap the buffers
        SDL_GL_SwapWindow(window);
        // Update the current position for the next iteration
        scene->black_coordinates[10][0] -= step_sizeX;
        scene->black_coordinates[10][2] -= step_sizeY;

    }

    scene->f4 = false;
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
