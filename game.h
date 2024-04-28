
#ifndef GAME_H
#define GAME_H


#include "Objects.h"
#include "Interact.h"
#include "graphics.h"
#include "menu.h"

struct Mouse {

    double x=   224;
    double y=  64;
    double head_w= 32;
    double head_h= 12;

    double dx = 0, dy = 0;
    double speed = INITIAL_SPEED;
    double speed2 = (double)speed/(sqrt(2));

    bool right = 1;


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

        if (dx > 0){
            right = 1;
        }else if (dx < 0){
            right = 0;
        }
    }


};


void updateDogPosition(Mouse &mouse, DOG &dog) {
    double distance = sqrt(pow(mouse.x - dog.x, 2) + pow(mouse.y - dog.y, 2));

    if (distance > dog.speed) {
        dog.dx= (mouse.x - dog.x ) / distance;
        dog.dy = (mouse.y - dog.y ) / distance;

        if (dog.dx > 0){
            dog.right = 1;
        }else if (dog.dx < 0){
            dog.right = 0;
        }

        dog.x += dog.dx * dog.speed;
        dog.y += dog.dy * dog.speed;

    } else {
        dog.x = mouse.x;
        dog.y = mouse.y;
    }
}

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
//Kiem tra va cham ngoai
int Collision1(const Mouse &mouse, const WALL wall){
    if (mouse.x + 32 > wall.x && mouse.x + 32 < wall.x + 5 && mouse.y + 32 > wall.y && mouse.y + 32 < wall.y + wall.h) return 1;
    if (mouse.x < wall.x + wall.w && mouse.x > wall.x +wall.w -5 && mouse.y + 32 > wall.y && mouse.y + 32< wall.y + wall.h) return 2;
    if (mouse.x + 32> wall.x && mouse.x< wall.x + wall.w && mouse.y + 32 > wall.y && mouse.y +32 < wall.y + 5) return 3;
    if (mouse.x + 32> wall.x && mouse.x< wall.x + wall.w && mouse.y + 32 < wall.y + wall.h && mouse.y + 32 > wall.y + wall.h - 5) return 4;
    return 0;

}
int Collision2(const Mouse &mouse, const OBJECTS &ob){
    if (mouse.x + 32 >= ob.x && mouse.x + 32 <= ob.x + 3 && mouse.y + 32 >= ob.y && mouse.y + 32 <= ob.y + ob.h) return 1;
    if (mouse.x <= ob.x + ob.w && mouse.x >= ob.x + ob.w - 3 && mouse.y + 32 >= ob.y && mouse.y + 32 <= ob.y + ob.h) return 2;
    if (mouse.x + 32 >= ob.x && mouse.x <= ob.x + ob.w && mouse.y + 32 >= ob.y && mouse.y + 32 <= ob.y + 3) return 3;
    if (mouse.x + 32 >= ob.x && mouse.x <= ob.x + ob.w && mouse.y + 32 <= ob.y + ob.h && mouse.y + 32 >= ob.y + ob.h - 3) return 4;
    return 0;
}

//Kiem tra ben trong
int Collision3(const Mouse &mouse, const OBJECTS &ob){
    if (mouse.x < ob.x + ob.w && mouse.x + 32 > ob.x && mouse.y < ob.y + ob.h -32 && mouse.y + 32 > ob.y) return 1;
    return 0;
}

int Collision3(const Mouse &mouse, const ZONE &z){
    if (mouse.x <= z.x + z.w && mouse.x + 32 >= z.x && mouse.y <= z.y + z.h -32&& mouse.y + 32 >= z.y) return 1;
    return 0;
}

int Collision3(const Mouse &mouse, const DOG &dog){
    if (mouse.x <= dog.x + dog.w && mouse.x + 32 >= dog.x && mouse.y <= dog.y + dog.h && mouse.y + 32 >= dog.y) return 1;
    return 0;
}
int Collision4(const Mouse &mouse, const DOG &dog){
    if (mouse.x <= dog.x + dog.w && mouse.x + mouse.head_w >= dog.x && mouse.y <= dog.y + dog.h && mouse.y + mouse.head_h >= dog.y) return 1;
    return 0;
}

void CheckCollisionWall(Mouse &mouse, vector<WALL> &walls) {
    for (const auto &wall : walls) {
        if (Collision1(mouse, wall) == 1) mouse.x = wall.x - 32;
        if (Collision1(mouse, wall) == 2) mouse.x = wall.x + wall.w;
        if (Collision1(mouse, wall) == 3) mouse.y = wall.y - 32;
        if (Collision1(mouse, wall) == 4) mouse.y = wall.y + wall.h - 32;

    }
}

void CheckNameObject(OBJECTS &ob, const Uint8* Key, TILEMAP &fullObjectsImage){
    if(ob.name == "singlesofa1") InteractX_X1(ob, Key, fullObjectsImage);
    if(ob.name == "singlesofa2") InteractX_X1(ob, Key, fullObjectsImage);
    if(ob.name == "doublesofa") InteractY_Y1(ob, Key, fullObjectsImage);
    if(ob.name == "clock") InteractY0_Y(ob, Key, fullObjectsImage);
    if(ob.name == "table") InteractXX1_YY1(ob, Key, fullObjectsImage);

}

void CheckCollisionObjects(Mouse &mouse, vector<OBJECTS> &objects, const Uint8* Keyy, TILEMAP &fullObjectsImage){

        for (auto &ob : objects){
            if (ob.exist){
                if (Collision2(mouse, ob)== 1){
                    mouse.x = ob.x - 32;
                    CheckNameObject(ob, Keyy, fullObjectsImage);
                }
                if (Collision2(mouse, ob)== 2){
                    mouse.x = ob.x + ob.w;
                    CheckNameObject(ob, Keyy, fullObjectsImage);
                }
                if (Collision2(mouse, ob)== 3){
                    mouse.y = ob.y - 32;
                    CheckNameObject(ob, Keyy, fullObjectsImage);
                }
                if (Collision2(mouse, ob)== 4){
                    mouse.y = ob.y + ob.h - 32;
                    CheckNameObject(ob, Keyy, fullObjectsImage);
                }
            }else{
                if (Collision3(mouse, ob)== 1){
                    CheckNameObject(ob, Keyy, fullObjectsImage);
                }

            }


        }

}

void CheckCollisionCamera(Mouse &mouse, const vector<ZONE> &camerascan, const bool &camnow){
    if (camnow){
        for (auto cs : camerascan){
            if (Collision3(mouse, cs)){
                if (cs.name == "CamScan1_1") cerr << "nguyhiem";
                if (cs.name == "CamScan2_1") cerr << "nguyhiem";
                if (cs.name == "CamScan3_1") cerr << "nguyhiem";
                if (cs.name == "CamScan4_1") cerr << "nguyhiem";

            }

        }
    }else{
        for (auto cs : camerascan){
            if (Collision3(mouse, cs)){
                if (cs.name == "CamScan1_2") cerr << "nguyhiem";
                if (cs.name == "CamScan2_2") cerr << "nguyhiem";
                if (cs.name == "CamScan3_2") cerr << "nguyhiem";
                if (cs.name == "CamScan4_2") cerr << "nguyhiem";

            }

        }
    }
}

void CheckNameVCL(const ZONE vcl, Graphics &graphics, const TILEMAP &fullObjectsImage){
    if (vcl.name == "singlesofa1") VCL2(vcl, graphics, fullObjectsImage);
}


void CheckCollisionObjectsToRender(const Mouse &mouse, const vector<ZONE> vungchelap,  Graphics &graphics, const TILEMAP &fullObjectsImage ){
    for (auto vcl : vungchelap){
        if (Collision3(mouse, vcl)) CheckNameVCL(vcl, graphics, fullObjectsImage);
    }

}



#endif // GAME_H
