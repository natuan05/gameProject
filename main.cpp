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
    SDL_Texture* sleepdog = graphics.loadTexture("img\\sleepdog.png");
    SDL_Texture* dogimage = graphics.loadTexture("img\\dog.png");

    vector<vector<int>> BackGround = loadTileMapFromCSV("Map\\gameDemo2_BackGround.csv");
    vector<vector<int>> Layer2 = loadTileMapFromCSV("Map\\gameDemo2_Layer2.csv");
    vector<vector<int>> ObjectsImage = loadTileMapFromCSV("Map\\gameDemo2_Object.csv");
    vector<vector<int>> ObjectsImage2 = loadTileMapFromCSV("Map\\gameDemo2_Objects2.csv");

    initObjectsImageCopy(ObjectsImage);
    vector<vector<int>> Camera1 = loadTileMapFromCSV("Map\\gameDemo2_Cam1.csv");
    vector<vector<int>> Camera2 = loadTileMapFromCSV("Map\\gameDemo2_Cam2.csv");
    vector<vector<int>> CamNow = Camera1;

    //Khoitaonhanvat
    SDL_Texture* characterRun= graphics.loadTexture(ROBBERRUN_SPRITE_FILE);
    Sprite RobberRun;
    RobberRun.init(characterRun, ROBBERRUN_FRAMES, ROBBERRUN_CLIPS);

    SDL_Texture* characterSlow= graphics.loadTexture(ROBBERSLOW_SPRITE_FILE);
    Sprite RobberSlow;
    RobberSlow.init(characterSlow, ROBBERSLOW_FRAMES, ROBBERSLOW_CLIPS);

    Mouse mouse;
    //KhoiTaoConCho
    DOG dog;
    SDL_Texture* dogrun= graphics.loadTexture(DOGRUN_SPRITE_FILE);
    Sprite DogRun;
    DogRun.init(dogrun, DOGRUN_FRAMES, DOGRUN_CLIPS);


    //KhoitaoObjects
    vector<WALL> walls = WallInit();
    vector<OBJECTS> objects= ObjectsInit();
    vector<CAMERASCAN> camerascan = CamScanInit();
    vector<VUNGCHELAP> vungchelap = VCLInit();
    VUNGCHODUOI vcd;
    VUNGCHODUOIInit(vcd);

    //Thoigiandoikhunghinh
    Uint32 prevTicks = SDL_GetTicks();
    Uint32 prevTicks2 = SDL_GetTicks();
    Uint32 prevTicks3 = SDL_GetTicks();
    Uint32 prevTicksForDogRun = SDL_GetTicks();

    //bool các thứ
    bool camnow(1);
    bool quit = false;
    bool menu= false;
    SDL_Event event;
    bool goR(0);
    bool dogchase(0);
    bool DoggoR(0);


    while (!quit) {
        //Lam menu
        while (menu){
            SDL_RenderClear(graphics.renderer);
        }

        SDL_RenderClear(graphics.renderer);
        graphics.drawTileMap(BackGround, tilesetImage);

        //VeObjects
        graphics.drawTileMap(ObjectsImage, tilesetImage);
        graphics.drawTileMap(ObjectsImage2, tilesetImage);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }

        //Cập nhật dx, dy theo bàn phím
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        mouse.UpdateDxDy( currentKeyStates);

        //chuyển frame theo thời gian chạy;
        if (mouse.isMoving()) {
            RobberRun.tick(prevTicks3);
            RobberSlow.tick(prevTicks);
        }

        const Uint8* KeySlow = SDL_GetKeyboardState(NULL);
        if (KeySlow[SDL_SCANCODE_LSHIFT]){
            mouse.dx /= 2;
            mouse.dy /= 2;
        }

        //cập nhật toạ độ
        if (mouse.dx > 0){
            goR = 1;
        }else if ( mouse.dx < 0){
            goR = 0;
        }

        mouse.move();

        //CheckCollision
        CheckBorder(mouse);
        CheckCollisionWall(mouse, walls);

        const Uint8* Keyy = SDL_GetKeyboardState(NULL);
        CheckCollisionObjects(mouse, objects, Keyy, ObjectsImage);

        //Render character

        if (KeySlow[SDL_SCANCODE_LSHIFT]){
            graphics.render(mouse.x, mouse.y, RobberSlow, goR);
        }else{
            graphics.render(mouse.x, mouse.y, RobberRun, goR);
        }


        //CheckDogChase
        if (dogchase == 0){
            if (Collision3(mouse, vcd)){
                if (!KeySlow[SDL_SCANCODE_LSHIFT]){
                    dogchase = 1;
                }
            }
        }
        if (dogchase){
            if (Collision3(mouse, vcd) && !Collision3(mouse, dog)){
                DogRun.tickdog(prevTicksForDogRun);
                updateDogPosition(mouse, dog, DoggoR);
                graphics.render(dog.x, dog.y, DogRun, DoggoR);
            }else{
                graphics.renderTexture(dogimage, dog.x, dog.y);
            }
        }else{
            graphics.renderTexture(sleepdog, 322, 465);
        }

        //CheckVCL
        CheckCollisionObjectsToRender(mouse, vungchelap, graphics, ObjectsImage, tilesetImage);


        //Vẽ layer2 giảm độ mờ
        SDL_SetTextureAlphaMod(tilesetImage, 100);
        graphics.drawTileMap(Layer2, tilesetImage);
        SDL_SetTextureAlphaMod(tilesetImage, 255);

        //Vẽ Camera
        graphics.drawCamera(Camera1, Camera2, CamNow, prevTicks2, tilesetImage, camnow);
        //CheckCamera
        CheckCollisionCamera(mouse, camerascan, camnow);

        graphics.presentScene();
        SDL_Delay(10);
    }

    graphics.quit();
    return 0;

}


