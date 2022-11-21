typedef struct Bullet
{
    float x;
    float y;
    float angle;
    float timeBeforeDeath;
    float momentumX;
    float momentumY;
    int isActive;
    int opacity;
    bool player;
} Bullet;