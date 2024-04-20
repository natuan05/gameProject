#ifndef _DEFS__H;

#define _DEFS__H

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 736;
const char* WINDOW_TITLE = "Hello World!";

const char* ROBBER_SPRITE_FILE = "img\\therobber.png";
const int ROBBER_CLIPS[][4] = {
    {  0, 0, 32, 32},
    { 32, 0, 32, 32},
    { 64, 0, 32, 32},
    { 96, 0, 32, 32},

    };
const int ROBBER_FRAMES = sizeof(ROBBER_CLIPS)/sizeof(int)/4;
const double MS_PER_FRAME= 250;

const int MAP_HEIGHT = 23;
const int MAP_WIDTH = 40;

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
//const int TILESET_NUM_COLS = 9;

const int MS_PER_CAMERA = 3000;
#endif // _DEFS__H
