#include "framebuffer.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static float depthBuffer[WIDTH][HEIGHT];
static char framebuffer[WIDTH][HEIGHT];

static char currentDraw = '*';

void setDrawChar(char color)
{
	currentDraw = color;
}

void clearFramebuffer(void)
{
	memset(depthBuffer, -10000, sizeof(depthBuffer));
	memset(framebuffer, '_', sizeof(framebuffer));
}

void printFramebuffer(void)
{
	for (int i = 0; i < WIDTH; i++)
	{
		printf("%.*s\n", WIDTH, framebuffer[i]);
	}
}

void drawPoint(vec3_t * point)
{
	int x = (WIDTH/2) + (int)point->x;
	int y = (HEIGHT/2) + (int)point->y;
	
	if (depthBuffer[x][y] > point->z)
		return;
		
	depthBuffer[x][y] = point->z;
	//if (point->x < WIDTH && point->y < HEIGHT)
	{
		//printf("%d-%d\n", (WIDTH/2) + (int)point->x, (HEIGHT/2) + (int)point->y);
		framebuffer[x][y] = currentDraw;
	}
}

void drawLine(vec3_t * p1, vec3_t * p2)
{
	//printf("%d %d - %d %d\n", (int)p1->x, (int)p1->y, (int)p2->x, (int)p2->y);
	int distance = abs(p2->x - p1->x) + abs(p2->y - p1->y);
	if (distance <= 2)
		return;
	vec3_t midpoint = {p1->x + (p2->x - p1->x)/2, p1->y + (p2->y - p1->y)/2, 0};
	drawPoint(&midpoint);
	drawLine(p1, &midpoint);
	drawLine(&midpoint, p2);
}

void drawScanLine(int y, vec3_t * pa, vec3_t * pb, vec3_t * pc, vec3_t * pd)
{
    // Thanks to current Y, we can compute the gradient to compute others values like
    // the starting X (sx) and ending X (ex) to draw between
    // if pa.Y == pb.Y or pc.Y == pd.Y, gradient is forced to 1
    float gradient1 = pa->y != pb->y ? (y - pa->y) / (pb->y - pa->y) : 1;
	float gradient2 = pc->y != pd->y ? (y - pc->y) / (pd->y - pc->y) : 1;
            
    int startx = pa->x + (pb->x - pa->x) * gradient1;
    int endx = pc->x + (pd->x - pc->x) * gradient2;
	
	float startz = pa->z + (pb->z - pa->z) * gradient1;
    float endz = pc->z + (pd->z - pc->z) * gradient2;

    // drawing a line from left (sx) to right (ex) 
	vec3_t linePoints = {startx, y, 0};
    for (linePoints.x = startx; linePoints.x < endx; linePoints.x++)
    {
		float gradientz = (linePoints.x - startx) / (float)(endx - startx);
		linePoints.z = startz + (endz - startz) * gradientz;
        drawPoint(&linePoints);
    }
}

void drawTriangle(vec3_t * p1, vec3_t * p2, vec3_t * p3)
{
    // Sorting the points in order to always have this order on screen p1, p2 & p3
    // with p1 always up (thus having the Y the lowest possible to be near the top screen)
    // then p2 between p1 & p3
    if (p1->y > p2->y)
    {
        vec3_t * temp = p2;
        p2 = p1;
        p1 = temp;
    }

    if (p2->y > p3->y)
    {
        vec3_t * temp = p2;
        p2 = p3;
        p3 = temp;
    }

    if (p1->y > p2->y)
    {
        vec3_t * temp = p2;
        p2 = p1;
        p1 = temp;
    }

    // inverse slopes
    float dP1P2, dP1P3;

    // http://en.wikipedia.org/wiki/Slope
    // Computing inverse slopes
    if (p2->y - p1->y > 0)
        dP1P2 = (p2->x - p1->x) / (p2->y - p1->y);
    else
        dP1P2 = 0;

    if (p3->y - p1->y > 0)
        dP1P3 = (p3->x - p1->x) / (p3->y - p1->y);
    else
        dP1P3 = 0;

    // Flat left sided triangles
    if (dP1P2 > dP1P3)
    {
        for (int y = (int)p1->y; y <= (int)p3->y; y++)
        {
            if (y < p2->y)
            {
                drawScanLine(y, p1, p3, p1, p2);
            }
            else
            {
                drawScanLine(y, p1, p3, p2, p3);
            }
        }
    }
    // Flat right sided triangle
    else
    {
        for (int y = (int)p1->y; y <= (int)p3->y; y++)
        {
            if (y < p2->y)
            {
                drawScanLine(y, p1, p2, p1, p3);
            }
            else
            {
                drawScanLine(y, p2, p3, p1, p3);
            }
        }
    }
}


/*
void drawLine(int x1, int y1, int x2, int y2)
{
	boolean changed;
	int x = x1;
	int y = y1;
	int dx = abs(x2 – x1);
	int dy = abs(y2 – y1);
	int signx = signum(x2 – x1);
	int signy = signum(y2 – y1);
	if (dy > dx)
	{
		swap(dx, dy);
		changed = true;
	}
	float e = 2 * dy - dx;
	for (int i = 1; i <= dx; i++)
	{
		framebuffer[x][y] = currentDraw;
		while (e >= 0)
		{
			if (changed)
				x = x + 1;
			else
				y = y + 1;
			e = e – 2 * dx;
		}
		if (changed)
			y += signy;
		else
			x += signx;
		e = e + 2 * dy;
	} 
}

void drawTriangleFlatBottom(Point p1, Point p2, Point p3)
{
	float invslope1 = (p2.x - p1.x) / (p2.y - p2.y);
	float invslope2 = (p3.x - p1.x) / (p3.y - p1.y);

	float currentx1 = p1.x;
	float currentx2 = p1.x;
	for (int scanlineY = p1.y; scanlineY <= p2.y; scanlineY++)
	{
		drawLine(currentx1, scanlineY, currentx2, scanlineY);
		currentx1 += invslope1;
		currentx2 += invslope2;
	}
}*/