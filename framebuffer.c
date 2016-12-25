#include "framebuffer.h"

#include <string.h>
#include <stdio.h>


static float depthBuffer[WIDTH][HEIGHT];
static char framebuffer[WIDTH][HEIGHT];

static char currentDraw = '*';

void setDrawChar(char color)
{
	currentDraw = color;
}

void clearFramebuffer(void)
{
	memset(framebuffer, '_', sizeof(framebuffer));
}

void printFramebuffer(void)
{
	for (int i = 0; i < WIDTH; i++)
	{
		printf("%.*s\n", WIDTH, framebuffer[i]);
	}
}

void drawPoint(Point * point)
{
	
	//if (point->x < WIDTH && point->y < HEIGHT)
	{
		//printf("%d-%d\n", (WIDTH/2) + (int)point->x, (HEIGHT/2) + (int)point->y);
		framebuffer[(WIDTH/2) + (int)point->x][(HEIGHT/2) + (int)point->y] = currentDraw;
	}
}

void drawSurface(Surface surface, char color)
{
	
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