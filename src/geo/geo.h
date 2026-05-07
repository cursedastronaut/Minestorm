#ifndef		GEO_H
# define	GEO_H
# include <toolbox.h>
# include "../app.h"

float2	rotatePoint(float2 p, float2 c, float angle);
bool	checkCollisionSquareSquare(float2 square1[4], float2 square2[4], App* app);

#endif