#ifndef DRAW_LINE_H
#define DRAW_LINE_H

typedef struct Color{
    int R;
    int G;
    int B;
}Color;

typedef struct Line{
    int x1;
    int x2;
    int y1;
    int y2;
    Color color;
}Line;

#endif
