#include "components.h"

void ui_element_new(gameObject* go, void (*onClick)(struct component*), void (*onClickRelease)(struct component*), void (*onPointerEnter)(struct component*), void (*onPointerExit)(struct component*)){
    ui_element* b = (ui_element*)malloc(sizeof(ui_element));
    component* c = __component_new(go);
    sprite* s = gameObject_get_component(c->owner, SPRITE_T);
    b->x = s->transform->pos.x;
    b->y = s->transform->pos.y;
    b->w = s->dst_rect.w;
    b->h = s->dst_rect.h;
    b->onClick = onClick;
    b->onClickRelease = onClickRelease;
    b->onPointerEnter = onPointerEnter;
    b->onPointerExit = onPointerExit;
    b->__inside = false;
    b->__clicked = false;

    c->init = ui_element_init;
    c->destroy = ui_element_destroy;
    c->update = ui_element_update;
    c->on_enable = ui_element_on_enable;
    c->on_disable = ui_element_on_disable;
    c->type = BUTTON_T;
    c->data = b;
}

void ui_element_init(component* comp){

}

void ui_element_update(component* c1){
    ui_element* b = (ui_element*)c1->data;
    int mouse_x;
    int mouse_y;
    Uint32 mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);
    SDL_MouseButtonEvent e;
    boolean box_inside = (mouse_x > b->x && mouse_x < b->x + b->w) && (mouse_y > b->y && mouse_y < b->y + b->h);
    if(!b->__inside){
        if(box_inside){
            b->__inside = true;
            b->onPointerEnter(c1);
        }
    }
    else //inside last frame
    {
        if(!box_inside){
            b->__inside = false;
            b->onPointerExit(c1);
        }
    }
    
    if(box_inside && !b->__clicked && c1->owner->__scene->__game->mouseState == 1){ //button down
        b->__clicked = true;
        b->onClick(c1);
    }
    else if(box_inside && b->__clicked && c1->owner->__scene->__game->mouseState == 0){ //button up
        b->onClickRelease(c1);
        b->__clicked = false;
    }
}

void ui_element_destroy(component* comp){
    ui_element* b = (ui_element*)comp->data;
    free(b);
}

void ui_element_on_enable(component* comp){

}

void ui_element_on_disable(component* comp){
    
}