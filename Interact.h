#ifndef INTERACT_H
#define INTERACT_H

#include "def.h"
#include "Map.h"
#include "graphics.h"
#include "structs.h"

void InteractXY(OBJECTS &ob, const Uint8* Key, TILEMAP &fullObjectsImage, BAG &Bag){
    int row= (ob.y)/TILE_HEIGHT;
    int col= (ob.x)/TILE_WIDTH;

    if (ob.exist){
        if (Key[SDL_SCANCODE_E]){
            ob.exist = 0;
            Bag.weight += ob.weight;
            Bag.money += ob.cost;
            fullObjectsImage.OI1[row][col] = -1;
        }

    }else{
        if (Key[SDL_SCANCODE_R]){
            ob.exist = 1;
            Bag.weight -= ob.weight;
            Bag.money -= ob.cost;
            fullObjectsImage.OI1[row][col] = fullObjectsImage.OI1CP[row][col];
        }

    }

}
void InteractY0_Y_OI2(OBJECTS &ob, const Uint8* Key, TILEMAP &fullObjectsImage, BAG &Bag){
    int row= (ob.y)/TILE_HEIGHT;
    int col= (ob.x)/TILE_WIDTH;

    if (ob.exist){
        if (Key[SDL_SCANCODE_E]){
            ob.exist = 0;
            Bag.weight += ob.weight;
            Bag.money += ob.cost;
            fullObjectsImage.OI2[row-1][col] = -1;
            fullObjectsImage.OI2[row][col] = -1;
        }

    }else{
        if (Key[SDL_SCANCODE_R]){
            ob.exist = 1;
            Bag.weight -= ob.weight;
            Bag.money -= ob.cost;
            fullObjectsImage.OI2[row-1][col] = fullObjectsImage.OI2CP[row-1][col];
            fullObjectsImage.OI2[row][col] = fullObjectsImage.OI2CP[row][col];        }

    }

}

void InteractY0_Y_Y1_OI2(OBJECTS &ob, const Uint8* Key, TILEMAP &fullObjectsImage, BAG &Bag){
    int row= (ob.y)/TILE_HEIGHT;
    int col= (ob.x)/TILE_WIDTH;

    if (ob.exist){
        if (Key[SDL_SCANCODE_E]){
            ob.exist = 0;
            Bag.weight += ob.weight;
            Bag.money += ob.cost;


            fullObjectsImage.OI2[row-1][col] = -1;
            fullObjectsImage.OI2[row][col] = -1;
            fullObjectsImage.OI2[row+1][col] = -1;
        }

    }else{
        if (Key[SDL_SCANCODE_R]){
            ob.exist = 1;
            Bag.weight -= ob.weight;
            Bag.money -= ob.cost;

            fullObjectsImage.OI2[row-1][col] = fullObjectsImage.OI2CP[row-1][col];
            fullObjectsImage.OI2[row][col] = fullObjectsImage.OI2CP[row][col];
            fullObjectsImage.OI2[row+1][col] = fullObjectsImage.OI2CP[row+1][col];
        }

    }

}



void VungCheKhuat_xy_OI1(const ZONE vcl,  Graphics &graphics, const TILEMAP &fullObjectsImage){
    int row= (vcl.y)/TILE_HEIGHT;
    int col= (vcl.x)/TILE_WIDTH;
    int x= col*32;
    int y= row*32;
    graphics.renderTile(x, y, fullObjectsImage.OI1[row][col], fullObjectsImage.tilesetImage);
}

void VungCheKhuat_xx1y_OI1(const ZONE vcl,  Graphics &graphics, const TILEMAP &fullObjectsImage){
    int row= (vcl.y)/TILE_HEIGHT;
    int col= (vcl.x)/TILE_WIDTH;
    int x= col*32;
    int y= row*32;
    graphics.renderTile(x, y, fullObjectsImage.OI1[row][col], fullObjectsImage.tilesetImage);
    graphics.renderTile(x + 32, y, fullObjectsImage.OI1[row][col+1], fullObjectsImage.tilesetImage);
}

void VungCheKhuat_xyy1_OI1(const ZONE vcl,  Graphics &graphics, const TILEMAP &fullObjectsImage){
    int row= (vcl.y)/TILE_HEIGHT;
    int col= (vcl.x)/TILE_WIDTH;
    int x= col*32;
    int y= row*32;
    graphics.renderTile(x, y, fullObjectsImage.OI1[row][col], fullObjectsImage.tilesetImage);
    graphics.renderTile(x, y+32, fullObjectsImage.OI1[row+1][col], fullObjectsImage.tilesetImage);
}

void VungCheKhuat_xyy1_OI2(const ZONE vcl,  Graphics &graphics, const TILEMAP &fullObjectsImage){
    int row= (vcl.y)/TILE_HEIGHT;
    int col= (vcl.x)/TILE_WIDTH;
    int x= col*32;
    int y= row*32;
    graphics.renderTile(x, y, fullObjectsImage.OI2[row][col], fullObjectsImage.tilesetImage);
    graphics.renderTile(x, y+32, fullObjectsImage.OI2[row+1][col], fullObjectsImage.tilesetImage);
}

void VungCheKhuat_xx1yy1_OI1(const ZONE vcl,  Graphics &graphics, const TILEMAP &fullObjectsImage){
    int row= (vcl.y)/TILE_HEIGHT;
    int col= (vcl.x)/TILE_WIDTH;
    int x= col*32;
    int y= row*32;
    graphics.renderTile(x, y, fullObjectsImage.OI1[row][col], fullObjectsImage.tilesetImage);
    graphics.renderTile(x + 32, y, fullObjectsImage.OI1[row][col+1], fullObjectsImage.tilesetImage);
    graphics.renderTile(x, y+32, fullObjectsImage.OI1[row+1][col], fullObjectsImage.tilesetImage);
    graphics.renderTile(x+32, y+32, fullObjectsImage.OI1[row+1][col+1], fullObjectsImage.tilesetImage);

}

void VungCheKhuat_xx1yy1_OI2(const ZONE vcl,  Graphics &graphics, const TILEMAP &fullObjectsImage){
    int row= (vcl.y)/TILE_HEIGHT;
    int col= (vcl.x)/TILE_WIDTH;
    int x= col*32;
    int y= row*32;
    graphics.renderTile(x, y, fullObjectsImage.OI2[row][col], fullObjectsImage.tilesetImage);
    graphics.renderTile(x + 32, y, fullObjectsImage.OI2[row][col+1], fullObjectsImage.tilesetImage);
    graphics.renderTile(x, y+32, fullObjectsImage.OI2[row+1][col], fullObjectsImage.tilesetImage);
    graphics.renderTile(x+32, y+32, fullObjectsImage.OI2[row+1][col+1], fullObjectsImage.tilesetImage);

}


#endif

