#include "math_3d.h"

#define WIDTH 128
#define HEIGHT WIDTH

typedef vec3_t * Surface[4];


void setDrawChar(char color);
void clearFramebuffer(void);
void printFramebuffer(void);
void drawPoint(vec3_t * point);