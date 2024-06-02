#ifndef MENU_PROCESSING_H_INCLUDED
#define MENU_PROCESSING_H_INCLUDED

#include "def.h"
#include "Objects.h"
#include "Interact.h"
#include "graphics.h"
#include "structs.h"


bool In_ButtonMap(const BUTTONS &Buttons){
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
    if (mouseX > Buttons.Bmap.x && mouseX < Buttons.Bmap.x + Buttons.Bmap.w &&
        mouseY > Buttons.Bmap.y && mouseY < Buttons.Bmap.y + Buttons.Bmap.h){
            return 1;
    }
    return 0;
}
bool In_ButtonMap2(const BUTTONS &Buttons){
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
    if (mouseX > Buttons.Bmap2.x && mouseX < Buttons.Bmap2.x + Buttons.Bmap2.w &&
        mouseY > Buttons.Bmap2.y && mouseY < Buttons.Bmap2.y + Buttons.Bmap2.h){
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
                            b.gamePlay1 = true;

                        }
                    }else{
                        buttonDown = false;
                    }

                }
            }

        }
    }else if (In_ButtonMap2(Buttons)){
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            bool buttonDown = true;
            while (buttonDown) {
                if (SDL_PollEvent(&e)) {
                    if(In_ButtonMap2(Buttons)){
                        if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                            buttonDown = false;
                            b.menu = false;
                            b.gamePlay1 = false;
                            b.gamePlay2 = true;

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
