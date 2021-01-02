#include "vec2.h"
#include <math.h>

vec2 vec2_new(float x, float y){
    vec2 v;
    v.x = x;
    v.y = y;
    return v;
}

vec2 vec2_add(vec2* v1, vec2* v2){
    vec2 v;
    v.x = v1->x + v2->x;
    v.y = v1->y + v2->y;
    return v;
}

vec2 vec2_sub(vec2* v1, vec2* v2){
    vec2 v;
    v.x = v1->x - v2->x;
    v.y = v1->y - v2->y;
    return v;
}

vec2 vec2_mul(vec2* v1, vec2* v2){
    vec2 v;
    v.x = v1->x * v2->x;
    v.y = v1->y * v2->y;
    return v;
}

float vec2_dot(vec2* v1, vec2* v2){
    return v1->x * v2->x + v1->y * v2->y;
}

float vec2_magn(vec2* v){
    return sqrtf(v->x * v->x + v->y * v->y);
}

vec2 vec2_norm(vec2* v){
    vec2 vec;
    float magn = vec2_magn(v);
    vec.x = v->x / magn;
    vec.y = v->y / magn;
    return vec;
}

vec2 vec2_mul_scal(vec2* v, float val){
    vec2 vec;
    vec.x = v->x * val;
    vec.y = v->y * val;
    return vec;
}
