#include <stdio.h>

struct Color{
    int r,g,b;
};

struct Line{
    int a,b;
    struct Color szin;
};
int main(){
    struct Line line1;
    line1.a=1;
    line1.b=3;
    line1.szin.r=255;
    line1.szin.g=255;
    line1.szin.b=255;
}
