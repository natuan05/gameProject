#include "def.h"
#include "graphics.h"
#include "game.h"
#include "Map.h"
#include "Objects.h"

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

void PlayMusic(Graphics &graphics){
    Mix_Music *BMusic = graphics.loadMusic("Music\\gloomy.mp3");
    graphics.play(BMusic);
}

void Draw_Background_Objects(TILEMAP &fullObjectsImage, Graphics &graphics){
    SDL_RenderClear(graphics.renderer);
    graphics.drawTileMap(fullObjectsImage.BackGround, fullObjectsImage.tilesetImage);
    graphics.drawTileMap(fullObjectsImage.OI1, fullObjectsImage.tilesetImage);
    graphics.drawTileMap(fullObjectsImage.OI2, fullObjectsImage.tilesetImage);

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
void GamePlay(bool &gameplay, bool &menu, Graphics &graphics){
    PlayMusic(graphics);

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
    TILEMAP fullObjectsImage;
    fullObjectsImage.init(tilesetImage, ObjectsImage1, ObjectsImage2);
    fullObjectsImage.BackGround = BackGround;

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
    vector<ZONE> camerascan = CamScanInit();
    vector<ZONE> vungchelap = VCLInit();
    ZONE vcd("vungchoduoi", 320, 0, 320, 737);
    vector<ZONE> escape = EscapeInit();
    ZONE hint("hint", 256, 256, 32, 32);

    //Thoigiandoikhunghinh
    Uint32 prevTicks = SDL_GetTicks();
    Uint32 prevTicks2 = SDL_GetTicks();
    Uint32 prevTicks3 = SDL_GetTicks();
    Uint32 prevTicksForDogRun = SDL_GetTicks();

    SPRITE_CHARACTER Sprite_Robber(RobberRun, RobberSlow);

    //bool các thứ
    bool camnow(1);
    SDL_Event event;
    bool dogchase(0);
    bool DoggoR(0);

    while(gameplay){
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT){
                gameplay = false;
                menu = true;
            }
        }

        Draw_Background_Objects(fullObjectsImage, graphics);

        Character_Move(mouse, graphics, Sprite_Robber);

        CheckBorder(mouse);
        CheckCollisionWall(mouse, walls);

        const Uint8* Keyy = SDL_GetKeyboardState(NULL);
        CheckCollisionObjects(mouse, objects, Keyy, fullObjectsImage);
        CheckCollisionObjectsToRender(mouse, vungchelap, graphics, fullObjectsImage);
        //CheckHint
        if(Collision3(mouse, hint)){
            if (Keyy[SDL_SCANCODE_E]){
                graphics.renderTexture(HintImage, 300, 0);
            }
        }
        //CheckCamera
        CheckCollisionCamera(mouse, camerascan, camnow);


        //CheckDogChase
        const Uint8* KeySlow = SDL_GetKeyboardState(NULL);
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
                if (Collision4(mouse, dog)){
                    if (KeySlow[SDL_SCANCODE_LSHIFT]){
                        graphics.render(mouse.x, mouse.y, RobberSlow, mouse.right);
                    }else{
                        graphics.render(mouse.x, mouse.y, RobberRun, mouse.right);
                    }
                }
            }
        }else{
            graphics.renderTexture(sleepdog, 322, 465);
        }

        //Vẽ layer2 giảm độ mờ
        SDL_SetTextureAlphaMod(tilesetImage, 100);
        graphics.drawTileMap(Layer2, tilesetImage);
        SDL_SetTextureAlphaMod(tilesetImage, 255);

        graphics.drawCamera(Camera1, Camera2, CamNow, prevTicks3, tilesetImage, camnow);

        graphics.renderTexture(nightImage, 0, 0);



        graphics.presentScene();

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


