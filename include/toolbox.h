#ifndef  TOOLBOX_H
# define TOOLBOX_H

#define COS_PI_2 0.0f
#define SIN_PI_2 1.0f

#define COS_PI_4 0.70710678f
#define SIN_PI_4 0.70710678f

#define COS_PI   -1.0f
#define SIN_PI    0.0f

#define PI 3.14159276

#include <stdbool.h>

typedef struct float2
{
	float x;
	float y;
} float2;

float2 newFloat2(float x, float y);
float2 rotatePoint(float2 p, float2 c, float angle);
bool	checkCollisionSquareSquare(float2 square1[4], float2 square2[4], bool shouldDrawCollision);

#endif