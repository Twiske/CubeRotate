
#include <stdio.h>
#include <math.h>

typedef struct{
	float x;
	float y;
	float z;
}Point;

typedef Point * Surface[4];

void rotate(float angleX, float angleY, Point cube[8])
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
}
float surfaceDepth(Surface surface)
{
	float averageDepth = 0;
	for (int i = 0; i < 4; i++)
	{
		averageDepth += surface[i]->z;
	}
	averageDepth /= 4;
}

int main()
{
	Point cube[8] = {{-1,-1,-1},
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
	
	rotate(1.0, M_PI/2.0, cube);
	
	/*for (int i = 0; i < 8; i++)
	{
		// Scale to right size
		cube[i].x = (cube[i].x + 1) * 30;
		cube[i].y = (cube[i].y + 1) * 30;
		cube[i].z = (cube[i].z + 1) * 30;
	}*/
	
	Surface * sortedSurfaces[6];
	
	
	for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			printf("%f,%f,%f\n", surfaces[j][i]->x, surfaces[j][i]->y, surfaces[j][i]->z);
		}
	}
	
}


