#ifndef BUTTON_H
#define BUTTON_H
#include "gameObject.h"

struct button{
    int w;
    int h;
    int x;
    int y;
    boolean __inside;
    boolean __clicked;
    void (*onClick)(struct component*);
    void (*onPointerEnter)(struct component*);
    void (*onPointerExit)(struct component*);
}; typedef struct button button;

void button_new(component* c, void (*onClick)(struct component*), void (*onPointerEnter)(struct component*), void (*onPointerExit)(struct component*));
void button_update(component* c1);
void button_init();

#endif