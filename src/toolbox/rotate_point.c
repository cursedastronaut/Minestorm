#include <toolbox.h>
#include <math.h>

float2 rotatePoint(float2 p, float2 c, float angle)
{
	float2 r;
	r.x = (p.x-c.x) * cosf(angle) - (p.y-c.y) * sinf(angle) + c.x;
	r.y = (p.y-c.y) * cosf(angle) + (p.x-c.x) * sinf(angle) + c.y;
	return r;
}