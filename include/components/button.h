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
    void (*onClickRelease)(struct component*);
}; typedef struct button button;

void button_new(gameObject* go, void (*onClick)(struct component*), void (*onClickRelease)(struct component*), 
                void (*onPointerEnter)(struct component*), void (*onPointerExit)(struct component*));
void button_update(component* c1);
void button_init(component* comp);
void button_destroy(component* comp);

#endif