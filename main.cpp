#include "def.h"
#include "graphics.h"
#include "game.h"
#include "Map.h"
#include "Objects.h"
#include "menu.h"

using namespace std;


void RunMenu(bool &menu, bool &gameplay, Graphics &graphics){

    SDL_Texture* menubackground = graphics.loadTexture("img\\menubackground.png");

    Mix_Music *gMusic = graphics.loadMusic("Music\\PinkPanther.mp3");
    graphics.play(gMusic);

    while(menu){
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT){
                    menu = false;
                    gameplay = true;
                }
        }
        SDL_RenderClear(graphics.renderer);
        graphics.renderTexture(menubackground, 0, 0);

        graphics.presentScene();
        SDL_Delay(10);
    }
    if (gMusic != nullptr) Mix_FreeMusic( gMusic );


}

void Draw_Background_Objects(TILEMAP &TileMap, Graphics &graphics){
    SDL_RenderClear(graphics.renderer);
    graphics.drawTileMap(TileMap.BackGround, TileMap.tilesetImage);
    graphics.drawTileMap(TileMap.OI1, TileMap.tilesetImage);
    graphics.drawTileMap(TileMap.OI2, TileMap.tilesetImage);

}

void Character_Move(Mouse &mouse, Graphics &graphics, SPRITE_CHARACTER &Sprite_Robber){
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        mouse.UpdateDxDy(currentKeyStates);
        if (mouse.isMoving()) {
            Sprite_Robber.Run.tick(Sprite_Robber.prevTicksR);
            Sprite_Robber.Slow.tick(Sprite_Robber.prevTicksS);
        }

        const Uint8* KeySlow = SDL_GetKeyboardState(NULL);
        if (KeySlow[SDL_SCANCODE_LSHIFT]){
            mouse.dx /= 2;
            mouse.dy /= 2;
        }
        mouse.move();
        if (KeySlow[SDL_SCANCODE_LSHIFT]){
            graphics.render(mouse.x, mouse.y, Sprite_Robber.Slow, mouse.right);
        }else{
            graphics.render(mouse.x, mouse.y, Sprite_Robber.Run, mouse.right);
        }

}

void DRAW_CAMERA(TILEMAP &TileMap, Graphics &graphics){
        Uint32 currentTicks = SDL_GetTicks();
        Uint32 deltaTicks = currentTicks - TileMap.prevTicksForCam;

        if (deltaTicks >= MS_PER_CAMERA){
            TileMap.CameraNow= (TileMap.CameraNow == TileMap.Camera1) ? TileMap.Camera2 : TileMap.Camera1;
            TileMap.cn= (TileMap.CameraNow == TileMap.Camera1) ? 1 : 0;
            TileMap.prevTicksForCam = currentTicks;
        }

        graphics.drawTileMap(TileMap.CameraNow, TileMap.tilesetImage);

}

void DRAW_LAYER2(TILEMAP &TileMap, Graphics &graphics, IMAGE &Image){
        SDL_SetTextureAlphaMod(TileMap.tilesetImage, 100);
        graphics.drawTileMap(TileMap.Layer2, TileMap.tilesetImage);
        SDL_SetTextureAlphaMod(TileMap.tilesetImage, 255);

        DRAW_CAMERA(TileMap, graphics);

        graphics.renderTexture(Image.NightMark, 0, 0);
        graphics.presentScene();
}

void CHECK_DOGCHASE(Mouse &mouse, DOG &dog, IMAGE &Image, Graphics &graphics, ZONE &vcd){
        const Uint8* KeySlow = SDL_GetKeyboardState(NULL);
        if (dog.dogchase == 0){
            if (Collision3(mouse, vcd)){
                if (!KeySlow[SDL_SCANCODE_LSHIFT]){
                    dog.dogchase = 1;
                }
            }
        }
        if (dog.dogchase){
            if (Collision3(mouse, vcd) && !Collision3(mouse, dog)){
                dog.DogRun.tickdog(dog.prevTicksForDogRun);
                updateDogPosition(mouse, dog);
                graphics.render(dog.x, dog.y, dog.DogRun, dog.right);

            }else{
                graphics.renderTexture(Image.DogImage, dog.x, dog.y);
            }
        }else{
            graphics.renderTexture(Image.SleepDog, 322, 465);
        }
}

void COLLISION_INTERACT(Mouse &mouse, TILEMAP &TileMap, WALL_OBJECTS_ZONE &woz, IMAGE &Image, Graphics &graphics ){
    CheckBorder(mouse);
    CheckCollisionWall(mouse, woz.walls);

    const Uint8* Keyy = SDL_GetKeyboardState(NULL);
    CheckCollisionObjects(mouse, woz.objects, Keyy, TileMap);
    CheckCollisionObjectsToRender(mouse, woz.vungchelap, graphics, TileMap);
    //CheckHint
    if(Collision3(mouse, woz.hint)){
        if (Keyy[SDL_SCANCODE_E]){
            graphics.renderTexture(Image.Hint1, 300, 0);
        }
    }
    //CheckCamera
    CheckCollisionCamera(mouse, woz.camerascan, TileMap.cn);

}

void GamePlay(bool &gameplay, bool &menu, Graphics &graphics){

    //Khởi tạo all image...
    SDL_Texture* tilesetImage= graphics.loadTexture("Map\\tilemap.png");
    vector<vector<int>> BackGround = loadTileMapFromCSV("Map\\gameDemo2_BackGround.csv");
    vector<vector<int>> Layer2 = loadTileMapFromCSV("Map\\gameDemo2_Layer2.csv");

    SDL_Texture* HintImage = graphics.loadTexture("img\\BeCarefulCamera.png");
    SDL_Texture* sleepdog = graphics.loadTexture("img\\sleepdog.png");
    SDL_Texture* dogimage = graphics.loadTexture("img\\dog.png");
    SDL_Texture* nightImage = graphics.loadTexture("img\\night.png");
    SDL_SetTextureAlphaMod(nightImage, 100);

    vector<vector<int>> ObjectsImage1 = loadTileMapFromCSV("Map\\gameDemo2_Object.csv");
    vector<vector<int>> ObjectsImage2 = loadTileMapFromCSV("Map\\gameDemo2_Objects2.csv");
    TILEMAP TileMap;
    TileMap.init(tilesetImage, ObjectsImage1, ObjectsImage2);
    TileMap.BackGround = BackGround;

    vector<vector<int>> Camera1 = loadTileMapFromCSV("Map\\gameDemo2_Cam1.csv");
    vector<vector<int>> Camera2 = loadTileMapFromCSV("Map\\gameDemo2_Cam2.csv");
    vector<vector<int>> CamNow = Camera1;

    TileMap.Camera1 = Camera1;
    TileMap.Camera2 = Camera2;
    TileMap.CameraNow = Camera1;

    TileMap.Layer2 = Layer2;

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
    dog.DogRun = DogRun;


    //KhoitaoObjects
    vector<WALL> walls = WallInit();
    vector<OBJECTS> objects= ObjectsInit();
    vector<ZONE> camerascan = CamScanInit();
    vector<ZONE> vungchelap = VCLInit();
    ZONE vcd("vungchoduoi", 320, 0, 320, 737);
    vector<ZONE> escape = EscapeInit();
    ZONE hint("hint", 256, 256, 32, 32);


    SPRITE_CHARACTER Sprite_Robber(RobberRun, RobberSlow);

    IMAGE Image;
    Image.DogImage = dogimage;
    Image.Hint1 = HintImage;
    Image.NightMark = nightImage;
    Image.SleepDog = sleepdog;

    WALL_OBJECTS_ZONE woz;
    woz.hint = hint;
    woz.objects = objects;
    woz.vungchelap = vungchelap;
    woz.walls = walls;
    woz.vungchoduoi = vcd;
    woz.camerascan = camerascan;

    SDL_Event event;

    while(gameplay){
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT){
                gameplay = false;
                menu = true;
            }
        }

        Draw_Background_Objects(TileMap, graphics);
        Character_Move(mouse, graphics, Sprite_Robber);
        COLLISION_INTERACT(mouse, TileMap, woz, Image, graphics);
        CHECK_DOGCHASE(mouse, dog, Image, graphics, vcd);
        DRAW_LAYER2(TileMap, graphics, Image);


        SDL_Delay(10);

    }

}

int main(int argc, char* argv[])
{
    bool quit = false;
    bool menu(1);
    bool gameplay(0);
    SDL_Event event;

    Graphics graphics;
    graphics.init();

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) quit = true;
        }
        if(menu){
            RunMenu(menu, gameplay, graphics);
        }else if(gameplay){
            GamePlay(gameplay, menu, graphics);
        }

    }

    graphics.quit();
    return 0;

}
