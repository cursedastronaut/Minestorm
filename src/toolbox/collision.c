#include "../app.h"
#include <toolbox.h>
#include <math.h>

typedef struct CollisionBounds
{
	float xMin, xMax;
	float yMin, yMax;
} CollisionBounds;

// Compute bounding box for a square
static CollisionBounds	getSquareBounds(float2 square[4])
{
	CollisionBounds bounds;

	bounds.xMin = bounds.xMax = square[0].x;
	bounds.yMin = bounds.yMax = square[0].y;

	for (int i = 1; i < 4; i++)
	{
		bounds.xMin = fminf(bounds.xMin, square[i].x);
		bounds.xMax = fmaxf(bounds.xMax, square[i].x);

		bounds.yMin = fminf(bounds.yMin, square[i].y);
		bounds.yMax = fmaxf(bounds.yMax, square[i].y);
	}

	return bounds;
}

// Collision logic only
static bool	processSquareSquareCollision(float2 square1[4], float2 square2[4])
{
	CollisionBounds b1 = getSquareBounds(square1);
	CollisionBounds b2 = getSquareBounds(square2);

	return (
		b1.xMax >= b2.xMin &&
		b1.xMin <= b2.xMax &&
		b1.yMax >= b2.yMin &&
		b1.yMin <= b2.yMax
	);
}

// Draw a square outline
static void	drawSquare(float2 square[4], unsigned int color)
{
	for (int i = 0; i < 4; ++i)
	{
		float2 point = square[i];
		float2 origin = {0, 0};

		point = rotatePoint(point, origin, 0);

		cvPathLineTo(point.x, point.y);
	}

	cvPathStroke(color, 1);
}

// Debug projection lines
static void	drawCollisionProjections(CollisionBounds b1, CollisionBounds b2)
{
	cvAddLine(b1.xMin, -3, b1.xMax, -3, CV_COL32(255, 255, 0, 255));
	cvAddLine(b2.xMin, -3, b2.xMax, -3, CV_COL32(255, 0, 255, 255));

	cvAddLine(17, b1.yMin, 17, b1.yMax, CV_COL32(255, 255, 0, 255));
	cvAddLine(17, b2.yMin, 17, b2.yMax, CV_COL32(255, 0, 255, 255));
}

// Visual rendering only
static void drawSquareCollision(
	float2 square1[4],
	float2 square2[4],
	bool shouldDrawCollision,
	bool collided)
{
	if (!shouldDrawCollision)
		return;

	CollisionBounds b1 = getSquareBounds(square1);
	CollisionBounds b2 = getSquareBounds(square2);

	drawCollisionProjections(b1, b2);

	unsigned int color = collided
		? CV_COL32(255, 0, 0, 255)
		: CV_COL32(255, 255, 255, 255);

	drawSquare(square1, color);
	drawSquare(square2, color);
}

// Main public function
bool	checkCollisionSquareSquare(float2 square1[4], float2 square2[4], bool shouldDrawCollision)
{
	bool collided = processSquareSquareCollision(square1, square2);

	drawSquareCollision(square1, square2, shouldDrawCollision, collided);

	return collided;
}