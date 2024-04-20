#include "def.h"
#include "graphics.h"
#include "game.h"
#include "Map.h"
#include "Objects.h"

using namespace std;


void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();
    //Khởi tạo all image...
    SDL_Texture* tilesetImage= graphics.loadTexture("Map\\tilemap.png");
    vector<vector<int>> BackGround = loadTileMapFromCSV("Map\\gameDemo2_BackGround.csv");
    vector<vector<int>> Layer2 = loadTileMapFromCSV("Map\\gameDemo2_Layer2.csv");
    vector<vector<int>> ObjectsImage = loadTileMapFromCSV("Map\\gameDemo2_Object.csv");
    initObjectsImage2(ObjectsImage);
    vector<vector<int>> Camera1 = loadTileMapFromCSV("Map\\gameDemo2_Cam1.csv");
    vector<vector<int>> Camera2 = loadTileMapFromCSV("Map\\gameDemo2_Cam2.csv");
    vector<vector<int>> CamNow = Camera1;

    SDL_Texture* character= graphics.loadTexture(ROBBER_SPRITE_FILE);
    Sprite Robber;
    Robber.init(character, ROBBER_FRAMES, ROBBER_CLIPS);


    Mouse mouse;
    mouse.x = SCREEN_WIDTH / 2 ;
    mouse.y = SCREEN_HEIGHT / 2;

    bool quit = false;
    SDL_Event event;

    vector<WALL> walls = WallInit();
    vector<OBJECTS> objects= ObjectsInit();
    vector<CAMERASCAN> camerascan = CamScanInit();

    Uint32 prevTicks = SDL_GetTicks();
    Uint32 prevTicks2 = SDL_GetTicks();

    while (!quit) {
        SDL_RenderClear(graphics.renderer);
        graphics.drawTileMap(BackGround, tilesetImage);

        graphics.drawTileMap(ObjectsImage, tilesetImage);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        //Cập nhật dx, dy theo bàn phím
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        mouse.UpdateDxDy( currentKeyStates);

        //chuyển frame theo thời gian chạy;
        if (mouse.isMoving()) {
            Robber.tick(prevTicks);
        }

        bool goR= (mouse.dx >= 0);

        mouse.move();

        //CheckCollision
        CheckBorder(mouse);
        CheckCollisionWall(mouse, walls);

        const Uint8* Keyy = SDL_GetKeyboardState(NULL);
        CheckCollisionObjects(mouse, objects, Keyy, ObjectsImage);

        //Render character
        graphics.render(mouse.x, mouse.y, Robber, goR);

        //Vẽ layer2 giảm độ mờ
        SDL_SetTextureAlphaMod(tilesetImage, 100);
        graphics.drawTileMap(Layer2, tilesetImage);
        SDL_SetTextureAlphaMod(tilesetImage, 255);

        //Vẽ Camera
        graphics.drawCamera(Camera1, Camera2, CamNow, prevTicks2, tilesetImage);
        //CheckCamera


        graphics.presentScene();
        SDL_Delay(10);
    }

    graphics.quit();

    return 0;

}


