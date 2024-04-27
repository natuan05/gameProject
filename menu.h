#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "def.h"
#include "graphics.h"

struct Inventory{
    map <OBJECTS, int> items;

};

struct SPRITE_CHARACTER{
    Sprite Run;
    Sprite Slow;

    Uint32 prevTicksR= SDL_GetTicks();
    Uint32 prevTicksS= SDL_GetTicks();

    SPRITE_CHARACTER(Sprite &_Run, Sprite &_Slow){
        Run = _Run;
        Slow = _Slow;
    }

};

#endif // MENU_H_INCLUDED
