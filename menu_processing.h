#ifndef MENU_PROCESSING_H_INCLUDED
#define MENU_PROCESSING_H_INCLUDED

#include "def.h"
#include "Objects.h"
#include "Interact.h"
#include "graphics.h"
#include "menu.h"

void MENU_BUTTONS_INIT(BUTTONS &Buttons){
    ZONE M("Mapbutton", 156, 126, 320, 110);
    ZONE S("Shopbutton", 156, 500, 320, 110);

    Buttons.Bmap = M;
    Buttons.Bshop = S;
}


bool In_ButtonMap(const BUTTONS &Buttons){
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
    if (mouseX > Buttons.Bmap.x && mouseX < Buttons.Bmap.x + Buttons.Bmap.w &&
        mouseY > Buttons.Bmap.y && mouseY < Buttons.Bmap.y + Buttons.Bmap.h){
            return 1;
    }
    return 0;
}

void Draw_ButtonMap(MENU_IMAGE &MImage){
    SDL_RenderClear(MImage.graphics.renderer);
    MImage.graphics.renderTexture(MImage.ButtonMap, 0, 0);
    MImage.graphics.presentScene();
}


void Check_Button(const BUTTONS &Buttons, BOOL &b, MENU_IMAGE &MImage, SDL_Event &e){
    if (In_ButtonMap(Buttons)){
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            bool buttonDown = true;
            while (buttonDown) {
                Draw_ButtonMap(MImage);
                if (SDL_PollEvent(&e)) {
                    if(In_ButtonMap(Buttons)){
                        if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                            buttonDown = false;
                            b.menu = false;
                            b.gamePlay = true;
                        }
                    }else{
                        buttonDown = false;
                    }

                }
            }

        }
    }
}

#endif // MENU_PROCESSING_H_INCLUDED
