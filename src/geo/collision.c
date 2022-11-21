#include <math.h>

bool checkCollisionPointTriangle(float2 triangle[3], float2 point, float angle)
{
    //Draw collision
     for (int i = 0; i <= 2; ++i)
        {
            float2 newPoint = triangle[i];
            float2 temp = newPoint;
            float2 xy = {0, 0};
            newPoint.x = rotatePoint(temp, xy, angle).x + point.x;
            newPoint.y = rotatePoint(temp, xy, angle).y + point.y;

            cvPathLineTo(newPoint.x, newPoint.y);
        }
        cvPathStroke(CV_COL32(255,0,0,255), 1);

    
}

bool checkCollisionSquareSquare(float2 square1[4], float2 square2[4])
{
    float xMin1, xMax1, xMin2, xMax2, yMin1, yMax1, yMin2, yMax2;
    for (int i = 1; i <= 3; i++)
    {
        //projection des deux carrés du point de vue du 1er carré.
        xMin1 = fminf(square1[i - 2].x, square1[i].x);
        xMax1 = fmaxf(square1[i - 2].x, square1[i].x);
        yMin1 = fminf(square1[i - 2].y, square1[i].y);
        yMax1 = fmaxf(square1[i - 2].y, square1[i].y);

        xMin2 = fminf(square2[i - 2].x, square2[i].x);
        xMax2 = fmaxf(square2[i - 2].x, square2[i].x);
        yMin2 = fminf(square2[i - 2].y, square2[i].y);
        yMax2 = fmaxf(square2[i - 2].y, square2[i].y);
    }

    //DEBUG projections
    cvAddLine(xMin1, -3, xMax1, -3, CV_COL32(255, 255, 0, 255));
    cvAddLine(xMin2, -3, xMax2, -3, CV_COL32(255, 0, 255, 255));
    cvAddLine(17, yMin1, 17, yMax1, CV_COL32(255, 255, 0, 255));
    cvAddLine(17, yMin2, 17, yMax2, CV_COL32(255, 0, 255, 255));
    //Détecte s'il y a une collision et dessine les boite de collisions
    // if (xMax1 <= xMin2 || yMax1 >= yMin2)
    if (xMax1 >= xMin2 && xMin1 <= xMax2  &&  yMax1 >= yMin2 && yMin1 <= yMax2)
    {
        
        for (int i = 0; i <= 3; ++i)
        {
            float2 newPoint = square1[i];
            float2 temp = newPoint;
            float2 xy = {0, 0};
            newPoint.x = rotatePoint(temp, xy, 0).x;
            newPoint.y = rotatePoint(temp, xy, 0).y;

            cvPathLineTo(newPoint.x, newPoint.y);
        }
        cvPathStroke(CV_COL32(255,0,0,255), 1);

        for (int i = 0; i <= 3; ++i)
        {
            float2 newPoint = square2[i];
            float2 temp = newPoint;
            float2 xy = {0, 0};
            newPoint.x = rotatePoint(temp, xy, 0).x;
            newPoint.y = rotatePoint(temp, xy, 0).y;

            cvPathLineTo(newPoint.x, newPoint.y);
        }
        cvPathStroke(CV_COL32(255,0,0,255), 1);

        return true;
    }
    else
    {
        for (int i = 0; i <= 3; ++i)
        {
            float2 newPoint = square1[i];
            float2 temp = newPoint;
            float2 xy = {0, 0};
            newPoint.x = rotatePoint(temp, xy, 0).x;
            newPoint.y = rotatePoint(temp, xy, 0).y;

            cvPathLineTo(newPoint.x, newPoint.y);
        }
        cvPathStroke(CV_COL32(255,255,255,255), 1);

        for (int i = 0; i <= 3; ++i)
        {
            float2 newPoint = square2[i];
            float2 temp = newPoint;
            float2 xy = {0, 0};
            newPoint.x = rotatePoint(temp, xy, 0).x;
            newPoint.y = rotatePoint(temp, xy, 0).y;

            cvPathLineTo(newPoint.x, newPoint.y);
        }
        cvPathStroke(CV_COL32(255,255,255,255), 1);
        return false;
    }
}