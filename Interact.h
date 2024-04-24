#ifndef INTERACT_H
#define INTERACT_H

#include "def.h"
#include "Map.h"
#include "graphics.h"

vector<vector<int>> ObjectsImageCopy ;

void InteractSingleSofa(OBJECTS &ob, const Uint8* Key, vector<vector<int>> &ObjectsImage);


void initObjectsImageCopy(vector<vector<int>> &ObjectsImage){
    ObjectsImageCopy = ObjectsImage;
}

void InteractX_X1(OBJECTS &ob, const Uint8* Key, vector<vector<int>> &ObjectsImage){
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
            ObjectsImage[row][col] = ObjectsImageCopy[row][col];
            ObjectsImage[row][col + 1] = ObjectsImageCopy[row][col + 1];
        }

    }

}
void InteractY_Y1(OBJECTS &ob, const Uint8* Key, vector<vector<int>> &ObjectsImage){
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
            ObjectsImage[row+1][col] = ObjectsImageCopy[row+1][col];
            ObjectsImage[row][col] = ObjectsImageCopy[row][col];
        }

    }


}

void InteractY0_Y(OBJECTS &ob, const Uint8* Key, vector<vector<int>> &ObjectsImage){
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
            ObjectsImage[row-1][col] = ObjectsImageCopy[row-1][col];
            ObjectsImage[row][col] = ObjectsImageCopy[row][col];
        }

    }


}
void InteractXX1_YY1(OBJECTS &ob, const Uint8* Key, vector<vector<int>> &ObjectsImage){
    int row= (ob.y)/TILE_HEIGHT;
    int col= (ob.x)/TILE_WIDTH;

    if (ob.exist){
        if (Key[SDL_SCANCODE_E]){
            ob.exist = 0;
            ObjectsImage[row+1][col] = -1;
            ObjectsImage[row][col] = -1;
            ObjectsImage[row][col+1] = -1;
            ObjectsImage[row+1][col+1] = -1;
        }

    }else{
        if (Key[SDL_SCANCODE_R]){
            ob.exist = 1;
            ObjectsImage[row+1][col] = ObjectsImageCopy[row+1][col];
            ObjectsImage[row][col] = ObjectsImageCopy[row][col];
            ObjectsImage[row][col+1] = ObjectsImageCopy[row][col+1];
            ObjectsImage[row+1][col+1] = ObjectsImageCopy[row+1][col+1];
        }

    }


}




//
void VCL1(const ZONE vcl,  Graphics &graphics, const vector<vector<int>> &ObjectsImage, SDL_Texture* tilesetImage){
    int row= (vcl.y)/TILE_HEIGHT;
    int col= (vcl.x)/TILE_WIDTH;
    int x= col*32;
    int y= row*32;
    graphics.renderTile(x, y, ObjectsImage[row][col], tilesetImage);
}

void VCL2(const ZONE vcl,  Graphics &graphics, const vector<vector<int>> &ObjectsImage, SDL_Texture* tilesetImage){
    int row= (vcl.y)/TILE_HEIGHT;
    int col= (vcl.x)/TILE_WIDTH;
    int x= col*32;
    int y= row*32;
    graphics.renderTile(x, y, ObjectsImage[row][col], tilesetImage);
    graphics.renderTile(x + 32, y, ObjectsImage[row][col+1], tilesetImage);
}



#endif

