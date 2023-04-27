#include "scene.h"

#include <OpenGL/gl.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void init_scene(Scene* scene)
{
    scene->sphere_angle = 0;
    scene->sphere_rotspeed = 0.01;
}

void update_scene(Scene* scene)
{
    scene->sphere_angle+=scene->sphere_rotspeed;
    if(scene->sphere_angle>360){
        scene->sphere_angle=0;
    }
}

void render_scene(const Scene* scene)
{
    draw_origin();
    //draw_triangle();
    draw_sphere(scene);
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

void draw_triangle()
{
    glBegin(GL_TRIANGLE_FAN);

    glColor3f(0, 1, 1);
    glVertex3f(0.5, 0.5, 0);
    glColor3f(1, 1, 0); 
    glVertex3f(0.5, 0, 0.5);
    glColor3f(1, 0, 1); 
    glVertex3f(0.5, 0.5, 0.5);

    glEnd();
}

void draw_sphere(Scene* scene)
{
    double r = 0.1;
    double x = 0 + 1*cos(degree_to_radian(scene->sphere_angle));
    double y = 0 + 0.5*sin(degree_to_radian(scene->sphere_angle));
    glTranslatef(x, y, 0.5);
    glRotatef(scene->sphere_angle*5, 0.0f, 0.0f, 1.6f);
    glTranslatef(-x, -y, -0.5);
    for(int theta=0; theta<=360; theta+=5){
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.5,0.5,0.5);
        for(int fi=-90; fi<=90; fi+=5){
            glVertex3f(r*cos(degree_to_radian(fi))*cos(degree_to_radian(theta)) + x, r*sin(degree_to_radian(fi))*cos(degree_to_radian(theta)) + y, r*sin(degree_to_radian(theta))+0.5);   
            glVertex3f(r*cos(degree_to_radian(fi))*cos(degree_to_radian(theta+5)) + x, r*sin(degree_to_radian(fi))*cos(degree_to_radian(theta+5)) + y, r*sin(degree_to_radian(theta+5))+0.5);   
        }
        glEnd();
    }
}
