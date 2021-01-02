#ifndef VEC2_H
#define VEC2_H

typedef struct {
    float x;
    float y;
} vec2;

vec2 vec2_new(float x, float y);
vec2 vec2_add(vec2* v1, vec2* v2);
vec2 vec2_sub(vec2* v1, vec2* v2);
vec2 vec2_mul(vec2* v1, vec2* v2);
float vec2_dot(vec2* v1, vec2* v2);
vec2 vec2_norm(vec2* v);
vec2 vec2_mul_scal(vec2* v, float val);
float vec2_magn(vec2* v1);

#endif