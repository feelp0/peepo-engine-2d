#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H
#include "gameObject.h"

struct ui_element{
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
}; typedef struct ui_element ui_element;

void ui_element_new(gameObject* go, void (*onClick)(struct component*), void (*onClickRelease)(struct component*), 
                void (*onPointerEnter)(struct component*), void (*onPointerExit)(struct component*));
void ui_element_update(component* c1);
void ui_element_init(component* comp);
void ui_element_destroy(component* comp);
void ui_element_on_enable(component* comp);
void ui_element_on_disable(component* comp);

#endif