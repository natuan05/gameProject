#ifndef MENU_PROCESSING_H_INCLUDED
#define MENU_PROCESSING_H_INCLUDED

#include "def.h"
#include "Objects.h"
#include "Interact.h"
#include "graphics.h"
#include "menu.h"


void CheckButton(BUTTONS &Buttons, BOOL &b){
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    if (mouseX > Buttons.Bmap.x && mouseX < Buttons.Bmap.x + Buttons.Bmap.w
        && mouseY > Buttons.Bmap.y && mouseY < Buttons.Bmap.y + Buttons.Bmap.h)
    {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                // Đợi cho đến khi nút chuột trái được thả ra
                bool buttonDown = true;
                while (buttonDown && SDL_WaitEvent(&e)) {
                    if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                        buttonDown = false;
                    }
                }

                // Sau khi nút chuột trái được thả ra, thực hiện hành động
                b.menu = false;
                b.gamePlay = true;
            }
        }
    }
}
#endif // MENU_PROCESSING_H_INCLUDED
