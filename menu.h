#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "def.h"
#include "graphics.h"
#include "Objects.h"

struct BOOL{
    bool quit = 0;
    bool gamePlay = 0;
    bool menu = 1;
    bool shop = 0;
};

struct SPRITE_CHARACTER{
    Sprite Run;
    Sprite Slow;

    Uint32 prevTicksR= SDL_GetTicks();
    Uint32 prevTicksS= SDL_GetTicks();

};

struct DOG{
    double x = 322;
    double y = 465;
    int w = 48;
    int h = 24;
    double dx = 0, dy = 0;
    double speed = INITIAL_DOGSPEED;

    bool dogchase = 0;
    bool right = 1;
    Uint32 prevTicksForDogRun = SDL_GetTicks();

    Sprite DogRun;
};


struct TILEMAP{
    Graphics graphics;
    SDL_Texture* tilesetImage;
    vector<vector<int>> OI1;
    vector<vector<int>> OI1CP;
    vector<vector<int>> OI2;
    vector<vector<int>> OI2CP;

    vector<vector<int>> BackGround;
    vector<vector<int>> Layer2;

    vector<vector<int>> Camera1;
    vector<vector<int>> Camera2;
    vector<vector<int>> CameraNow;
    Uint32 prevTicksForCam = SDL_GetTicks();
    bool cn = 1;

    void init(SDL_Texture* _tilesetImage, vector<vector<int>> _OI1, vector<vector<int>> _OI2){
        tilesetImage = _tilesetImage;
        OI1 = _OI1;
        OI2 = _OI2;
        OI1CP = OI1;
        OI2CP = OI2;
    }



};

struct IMAGE{
    Graphics graphics;
    SDL_Texture* SleepDog;
    SDL_Texture* DogImage;
    SDL_Texture* NightMark;
    SDL_Texture* Hint1;
    SDL_Texture* DogRuns;
    SDL_Texture* Busted;
};

struct MENU_IMAGE{
    Graphics graphics;
    SDL_Texture* MenuBackground;
    SDL_Texture* ButtonMap;

};

struct WALL_OBJECTS_ZONE{
    Graphics graphics;
    vector<WALL> walls;
    vector<OBJECTS> objects;
    vector<ZONE> vungchelap;
    vector<ZONE> camerascan;

    ZONE vungchoduoi;
    ZONE hint;
};

struct BUTTONS{
    ZONE Bshop;
    ZONE Bmap;

};

#endif // MENU_H_INCLUDED
