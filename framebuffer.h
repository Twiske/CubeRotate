

#define WIDTH 64
#define HEIGHT WIDTH

typedef struct{
	float x;
	float y;
	float z;
}Point;

typedef Point * Surface[4];


void setDrawChar(char color);
void clearFramebuffer(void);
void printFramebuffer(void);
void drawPoint(Point * point);