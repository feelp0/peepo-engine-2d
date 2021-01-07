#ifndef COMMON_H
#define COMMON_H
//#include "SDL.h"
#include "SDL_image.h"
#include <stdlib.h>

enum boolean_enum { true = 1, false = 0 };
typedef unsigned char boolean;
typedef unsigned int uint;

int GetRandomInt(int max);

int GetRandomIntBetween(int max, int min);

float GetRandomFloat(float max);

float GetRandomFloatBetween(float max, float min);

#endif //COMMON