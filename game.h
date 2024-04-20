
#ifndef GAME_H
#define GAME_H

#define INITIAL_SPEED 1.5

#include "graphics.h"
#include "Objects.h"
#include "Interact.h"

void CheckNameObject(OBJECTS &ob, const Uint8* Key,vector<vector<int>> &ObjectsImage);

struct Mouse {
    double x, y;
    double dx = 0, dy = 0;
    double speed = INITIAL_SPEED;
    double speed2 = (double)speed/(sqrt(2));

    void move() {
        x += dx;
        y += dy;
        dx = 0;
        dy= 0;

    }
    void turnNorth() {
        dy = -speed;
        dx = 0;
    }
    void turnSouth() {
        dy = speed;
        dx = 0;
    }
    void turnWest() {
        dy = 0;
        dx = -speed;
    }
    void turnEast() {
        dy = 0;
        dx = speed;
    }
    void stop(){
        dx = 0;
        dy = 0;
    }

    bool isMoving() {
        return (dx != 0 || dy != 0);
    }

    void UpdateDxDy(const Uint8* currentKeyStates){

        if (currentKeyStates[SDL_SCANCODE_S]) turnSouth();
        if (currentKeyStates[SDL_SCANCODE_W]) turnNorth();
        if (currentKeyStates[SDL_SCANCODE_A]) turnWest();
        if (currentKeyStates[SDL_SCANCODE_D]) turnEast();

        const int directions[][2] = {
            {SDL_SCANCODE_W, SDL_SCANCODE_A},
            {SDL_SCANCODE_W, SDL_SCANCODE_D},
            {SDL_SCANCODE_S, SDL_SCANCODE_D},
            {SDL_SCANCODE_S, SDL_SCANCODE_A},

        };

        for (const auto& dir : directions) {
            bool allPressed = true;
            for (const auto& key : dir) {
                if (!currentKeyStates[key]) {
                    allPressed = false;
                    break;
                }
            }

            if (allPressed) {
                dx = (dir[1] == SDL_SCANCODE_A) ? -speed2 : speed2;
                dy = (dir[0] == SDL_SCANCODE_W) ? -speed2 : speed2;
                break;
            }
        }



    }


};

void CheckBorder (Mouse &mouse){
    if ( mouse.x < 0){
        mouse.x= 0;
    }
    if( mouse.x+32 > SCREEN_WIDTH ){
        mouse.x = SCREEN_WIDTH -32;
    }

    if (mouse.y < 0){
        mouse.y= 0;
    }
    if ( mouse.y +32 > SCREEN_HEIGHT){
        mouse.y= SCREEN_HEIGHT-32;
    }

}

int Collision1(Mouse &mouse, const WALL wall){
    if (mouse.x + 32 > wall.x && mouse.x + 32 < wall.x + 5 && mouse.y + 32 > wall.y && mouse.y + 32 < wall.y + wall.h) return 1;
    if (mouse.x < wall.x + wall.w && mouse.x > wall.x +wall.w -5 && mouse.y + 32 > wall.y && mouse.y + 32< wall.y + wall.h) return 2;
    if (mouse.x + 32> wall.x && mouse.x< wall.x + wall.w && mouse.y + 32 > wall.y && mouse.y +32 < wall.y + 5) return 3;
    if (mouse.x + 32> wall.x && mouse.x< wall.x + wall.w && mouse.y + 32 < wall.y + wall.h && mouse.y + 32 > wall.y + wall.h - 5) return 4;
    return 0;

}

int Collision2(Mouse &mouse, const OBJECTS &ob){
    if (mouse.x + 32 >= ob.x && mouse.x + 32 <= ob.x + 3 && mouse.y + 32 >= ob.y && mouse.y + 32 <= ob.y + ob.h) return 1;
    if (mouse.x <= ob.x + ob.w && mouse.x >= ob.x + ob.w - 3 && mouse.y + 32 >= ob.y && mouse.y + 32 <= ob.y + ob.h) return 2;
    if (mouse.x + 32 >= ob.x && mouse.x <= ob.x + ob.w && mouse.y + 32 >= ob.y && mouse.y + 32 <= ob.y + 3) return 3;
    if (mouse.x + 32 >= ob.x && mouse.x <= ob.x + ob.w && mouse.y + 32 <= ob.y + ob.h && mouse.y + 32 >= ob.y + ob.h - 3) return 4;
    return 0;
}

int Collision3(Mouse &mouse, const OBJECTS &ob){
    if (mouse.x + 32 >= ob.x && mouse.x + 32 <= ob.x + 10 && mouse.y + 32 >= ob.y && mouse.y + 32 <= ob.y + ob.h) return 1;
    if (mouse.x <= ob.x + ob.w && mouse.x >= ob.x + ob.w - 10 && mouse.y + 32 >= ob.y && mouse.y + 32 <= ob.y + ob.h) return 2;
    if (mouse.x + 32 >= ob.x && mouse.x <= ob.x + ob.w && mouse.y + 32 >= ob.y && mouse.y + 32 <= ob.y + 10) return 3;
    if (mouse.x + 32 >= ob.x && mouse.x <= ob.x + ob.w && mouse.y + 32 <= ob.y + ob.h && mouse.y + 32 >= ob.y + ob.h - 10) return 4;
    return 0;
}

void CheckCollisionWall(Mouse &mouse, const vector<WALL> &walls) {
    for (const auto &wall : walls) {
        if (Collision1(mouse, wall) == 1) mouse.x = wall.x - 32;
        if (Collision1(mouse, wall) == 2) mouse.x = wall.x + wall.w;
        if (Collision1(mouse, wall) == 3) mouse.y = wall.y - 32;
        if (Collision1(mouse, wall) == 4) mouse.y = wall.y + wall.h - 32;

    }
}

void CheckCollisionObjects(Mouse &mouse, vector<OBJECTS> &objects, const Uint8* Keyy, vector<vector<int>> &ObjectsImage){

        for (auto &ob : objects){
            if (ob.exist){
                if (Collision2(mouse, ob)== 1){
                    mouse.x = ob.x - 32;
                    CheckNameObject(ob, Keyy, ObjectsImage);
                }
                if (Collision2(mouse, ob)== 2){
                    mouse.x = ob.x + ob.w;
                    CheckNameObject(ob, Keyy, ObjectsImage);
                }
                if (Collision2(mouse, ob)== 3){
                    mouse.y = ob.y - 32;
                    CheckNameObject(ob, Keyy, ObjectsImage);
                }
                if (Collision2(mouse, ob)== 4){
                    mouse.y = ob.y + ob.h - 32;
                    CheckNameObject(ob, Keyy, ObjectsImage);
                }
            }else{
                if (Collision3(mouse, ob)== 1){
                    CheckNameObject(ob, Keyy, ObjectsImage);
                }
                if (Collision3(mouse, ob)== 2){
                    CheckNameObject(ob, Keyy, ObjectsImage);
                }
                if (Collision3(mouse, ob)== 3){
                    CheckNameObject(ob, Keyy, ObjectsImage);
                }
                if (Collision3(mouse, ob)== 4){
                    CheckNameObject(ob, Keyy, ObjectsImage);
                }
            }


        }

}

void CheckNameObject(OBJECTS &ob, const Uint8* Key, vector<vector<int>> &ObjectsImage){
    if(ob.name == "singlesofa1") InteractSingleSofa(ob, Key, ObjectsImage);
    if(ob.name == "singlesofa2") InteractSingleSofa(ob, Key, ObjectsImage);
    if(ob.name == "doublesofa") InteractDoubleSofa(ob, Key, ObjectsImage);
    if(ob.name == "clock") InteractClock(ob, Key, ObjectsImage);

}

#endif // GAME_H
