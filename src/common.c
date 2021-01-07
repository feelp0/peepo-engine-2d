#include "common.h"

int GetRandomInt(int max)
{
    return rand() % max;
}

int GetRandomIntBetween(int max, int min)
{
    return (rand() % (max + 1 - min)) + min;
}

float GetRandomFloat(float max)
{
    return (float)rand() / (float)(RAND_MAX / max);
}

float GetRandomFloatBetween(float max, float min)
{
    return (((float)rand() / (float)RAND_MAX) * (max - min)) + min;
}