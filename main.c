
#include <stdio.h>
#include <math.h>

#define MATH_3D_IMPLEMENTATION
#import "math_3d.h"
#include "framebuffer.h"

/*
void rotate(float angleX, float angleY, vec3_t point)
{
	for (int i = 0; i < 8; i++)
	{
		float x = cube[i].x;
		float y = cube[i].y;
		float z = cube[i].z;
		
		cube[i].x = x * cos(angleX) - z * sin(angleX);
		cube[i].z = z * cos(angleX) + x * sin(angleX);
		
		z = cube[i].z;
		
		cube[i].y = y * cos(angleY) - z * sin(angleY);
		cube[i].z = z * cos(angleY) + y * sin(angleY);
	}
}*/

/*
float surfaceDepth(Surface surface)
{
	float averageDepth = 0;
	for (int i = 0; i < 4; i++)
	{
		averageDepth += surface[i]->z;
	}
	averageDepth /= 4;
	return 0;
}*/

int main()
{
	mat4_t rotationMatrix = m4_rotation(M_PI/20, (vec3_t){1,.5,.4});
	vec3_t cube[8] = {{-1,-1,-1},
	                 {-1,-1, 1},
			 {-1, 1,-1},
			 {-1, 1, 1},
			 { 1,-1,-1},
			 { 1,-1, 1},
			 { 1, 1,-1},
			 { 1, 1, 1}};
					 


	Surface surfaces[6] = {
		{&cube[0], &cube[1], &cube[3], &cube[2]},
		{&cube[4], &cube[5], &cube[7], &cube[6]},
		{&cube[0], &cube[1], &cube[5], &cube[4]},
		{&cube[2], &cube[3], &cube[7], &cube[6]},
		{&cube[0], &cube[2], &cube[6], &cube[4]},
		{&cube[1], &cube[3], &cube[7], &cube[5]}};
	
	//rotate(1.0, M_PI/2.0, cube);

	for (int i = 0; i < 8; i++)
	{
		// Scale to right size
		cube[i].x = (cube[i].x ) * 20;
		cube[i].y = (cube[i].y ) * 20;
		cube[i].z = (cube[i].z ) * 20;
	}
	
//	Surface * sortedSurfaces[6];
	
	while(1)
	{
		clearFramebuffer();
		
		for (int i = 0; i < 8; i++)
		{
			
			cube[i] = m4_mul_pos(rotationMatrix, cube[i]);
		}
		/*
		for (int i = 0; i < 7; i++)
		{
			setDrawChar('0' + i);
			//drawPoint(&cube[i]);
			
			drawLine(&cube[i], &cube[i+1]);
			//printf("\n");
		}*/
		for (int j = 0; j < 6; j++)
		{
			setDrawChar(j + '*');
			//drawLine(surfaces[j][0], surfaces[j][1]);
			//drawLine(surfaces[j][1], surfaces[j][2]);
			//drawLine(surfaces[j][2], surfaces[j][3]);
			//drawLine(surfaces[j][3], surfaces[j][0]);
			drawTriangle(surfaces[j][0], surfaces[j][1], surfaces[j][2]);
			drawTriangle(surfaces[j][0], surfaces[j][2], surfaces[j][3]);
		}
		printFramebuffer();
		usleep(300 * 1000);
		
		//rotate(M_PI/40, M_PI/30.0, cube);
	}
}


