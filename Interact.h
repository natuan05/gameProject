#ifndef INTERACT_H
#define INTERACT_H

#include "def.h"
#include "Map.h"

vector<vector<int>> ObjectsImage2 ;

void InteractSingleSofa(OBJECTS &ob, const Uint8* Key, vector<vector<int>> &ObjectsImage);


void initObjectsImage2(vector<vector<int>> &ObjectsImage){
    ObjectsImage2 = ObjectsImage;
}
void InteractSingleSofa(OBJECTS &ob, const Uint8* Key, vector<vector<int>> &ObjectsImage){
    int row= (ob.y)/TILE_HEIGHT;
    int col= (ob.x)/TILE_WIDTH;

    if (ob.exist){
        if (Key[SDL_SCANCODE_E]){
            ob.exist = 0;
            ObjectsImage[row][col] = -1;
            ObjectsImage[row][col + 1] = -1;
        }

    }else{
        if (Key[SDL_SCANCODE_R]){
            ob.exist = 1;
            ObjectsImage[row][col] = ObjectsImage2[row][col];
            ObjectsImage[row][col + 1] = ObjectsImage2[row][col + 1];
        }

    }

}
void InteractDoubleSofa(OBJECTS &ob, const Uint8* Key, vector<vector<int>> &ObjectsImage){
    int row= (ob.y)/TILE_HEIGHT;
    int col= (ob.x)/TILE_WIDTH;

    if (ob.exist){
        if (Key[SDL_SCANCODE_E]){
            ob.exist = 0;
            ObjectsImage[row+1][col] = -1;
            ObjectsImage[row][col] = -1;
        }

    }else{
        if (Key[SDL_SCANCODE_R]){
            ob.exist = 1;
            ObjectsImage[row+1][col] = ObjectsImage2[row+1][col];
            ObjectsImage[row][col] = ObjectsImage2[row][col];
        }

    }


}

void InteractClock(OBJECTS &ob, const Uint8* Key, vector<vector<int>> &ObjectsImage){
    int row= (ob.y)/TILE_HEIGHT;
    int col= (ob.x)/TILE_WIDTH;

    if (ob.exist){
        if (Key[SDL_SCANCODE_E]){
            ob.exist = 0;
            ObjectsImage[row-1][col] = -1;
            ObjectsImage[row][col] = -1;
        }

    }else{
        if (Key[SDL_SCANCODE_R]){
            ob.exist = 1;
            ObjectsImage[row-1][col] = ObjectsImage2[row-1][col];
            ObjectsImage[row][col] = ObjectsImage2[row][col];
        }

    }


}




#endif

