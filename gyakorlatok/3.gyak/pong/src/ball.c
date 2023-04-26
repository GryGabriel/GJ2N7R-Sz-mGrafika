#include "ball.h"

#include <GLFW/glfw3.h>

#include <math.h>

void init_ball(Ball* ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
    ball->radius = 50;
    ball->speed_x = 300;
    ball->speed_y = 300;
    ball->rotation = 30;
}

void update_ball(Ball* ball, double time, float radius, float rotation_speed)
{
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;
    if(radius > 10 && radius < 100) ball->radius = radius;
    ball->rotation += rotation_speed * time;
}

void render_ball(Ball* ball)
{
    double angle;
    double x;
    double y;

    glPushMatrix();
    glTranslatef(ball->x, ball->y, 0.0);
    glRotatef(ball->rotation, 0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.9, 0.8);
    glVertex2f(0, 0);
    angle = 0;
    while (angle < 2.0 * M_PI + 1) {
        x = cos(angle) * ball->radius;
        y = sin(angle) * ball->radius;
        glVertex2f(x, y);
        angle += 0.9;
    }
    glEnd();
    glPopMatrix();
}
