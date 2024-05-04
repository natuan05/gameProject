#include "def.h"
#include "graphics.h"
#include "game.h"
#include "Map.h"
#include "Objects.h"
#include "menu.h"
#include "menu_processing.h"

using namespace std;

void MENU_IMAGE_INIT(Graphics &graphics, MENU_IMAGE &MImage){
    SDL_Texture* menubackground = graphics.loadTexture("img\\menubackground.png");
    SDL_Texture* ButtonMap = graphics.loadTexture("img\\PressMapButton.png");

    MImage.graphics = graphics;
    MImage.MenuBackground = menubackground;
    MImage.ButtonMap = ButtonMap;

}

void DRAW_MENU(MENU_IMAGE &MImage){
    SDL_RenderClear(MImage.graphics.renderer);
    MImage.graphics.renderTexture(MImage.MenuBackground, 0, 0);
    MImage.graphics.presentScene();
}

void RunMenu(BOOL &b, Graphics &graphics){

    MENU_IMAGE MImage;
    MENU_IMAGE_INIT(graphics, MImage);

    BUTTONS Buttons;
    MENU_BUTTONS_INIT(Buttons);

    Mix_Music *gMusic = graphics.loadMusic("Music\\PinkPanther.mp3");
    graphics.play(gMusic);

    while(b.menu){
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT){
                    b.menu = 0;
                    b.quit = 1;
                }else{
                    Check_Button(Buttons, b, MImage, e);
                }
        }

        DRAW_MENU(MImage);

        SDL_Delay(10);
    }
    if (gMusic != nullptr) Mix_FreeMusic( gMusic );
}

void TILEMAP_INIT(TILEMAP &TileMap, Graphics &graphics){
    SDL_Texture* tilesetImage= graphics.loadTexture("Map\\tilemap.png");
    vector<vector<int>> BackGround = loadTileMapFromCSV("Map\\gameDemo2_BackGround.csv");
    vector<vector<int>> Layer2 = loadTileMapFromCSV("Map\\gameDemo2_Layer2.csv");
    vector<vector<int>> ObjectsImage1 = loadTileMapFromCSV("Map\\gameDemo2_Object.csv");
    vector<vector<int>> ObjectsImage2 = loadTileMapFromCSV("Map\\gameDemo2_Objects2.csv");
    vector<vector<int>> Camera1 = loadTileMapFromCSV("Map\\gameDemo2_Cam1.csv");
    vector<vector<int>> Camera2 = loadTileMapFromCSV("Map\\gameDemo2_Cam2.csv");
    vector<vector<int>> CamNow = Camera1;

    TileMap.graphics = graphics;
    TileMap.init(tilesetImage, ObjectsImage1, ObjectsImage2);
    TileMap.BackGround = BackGround;
    TileMap.Camera1 = Camera1;
    TileMap.Camera2 = Camera2;
    TileMap.CameraNow = Camera1;
    TileMap.Layer2 = Layer2;
}

void IMAGE_INIT(IMAGE &Image, Graphics &graphics){
    SDL_Texture* HintImage = graphics.loadTexture("img\\BeCarefulCamera.png");
    SDL_Texture* sleepdog = graphics.loadTexture("img\\sleepdog.png");
    SDL_Texture* dogimage = graphics.loadTexture("img\\dog.png");
    SDL_Texture* dogruns= graphics.loadTexture(DOGRUN_SPRITE_FILE);
    SDL_Texture* nightImage = graphics.loadTexture("img\\night.png");
    SDL_SetTextureAlphaMod(nightImage, 100);
    SDL_Texture* Busted = graphics.loadTexture("img\\Busted.png");

    Image.graphics = graphics;
    Image.DogImage = dogimage;
    Image.Hint1 = HintImage;
    Image.NightMark = nightImage;
    Image.SleepDog = sleepdog;
    Image.DogRuns = dogruns;
    Image.Busted = Busted;
}

void WOZ_INIT(WALL_OBJECTS_ZONE &woz, Graphics &graphics){
    vector<WALL> walls = WallInit();
    vector<OBJECTS> objects= ObjectsInit();
    vector<ZONE> camerascan = CamScanInit();
    vector<ZONE> vungchelap = VCLInit();
    ZONE vcd("vungchoduoi", 320, 0, 320, 737);
    ZONE hint("hint", 256, 256, 32, 32);

    woz.hint = hint;
    woz.objects = objects;
    woz.vungchelap = vungchelap;
    woz.walls = walls;
    woz.vungchoduoi = vcd;
    woz.camerascan = camerascan;
}

void SPRITE_CHARACTER_INIT(Graphics &graphics, SPRITE_CHARACTER &Sprite_Robber){
    SDL_Texture* characterRun= graphics.loadTexture(ROBBERRUN_SPRITE_FILE);
    Sprite RobberRun;
    RobberRun.init(characterRun, ROBBERRUN_FRAMES, ROBBERRUN_CLIPS);

    SDL_Texture* characterSlow= graphics.loadTexture(ROBBERSLOW_SPRITE_FILE);
    Sprite RobberSlow;
    RobberSlow.init(characterSlow, ROBBERSLOW_FRAMES, ROBBERSLOW_CLIPS);

    Sprite_Robber.Run = RobberRun;
    Sprite_Robber.Slow = RobberSlow;


}

void DRAW_BACKGROUND_OBJECTS(TILEMAP &TileMap){
    SDL_RenderClear(TileMap.graphics.renderer);
    TileMap.graphics.drawTileMap(TileMap.BackGround, TileMap.tilesetImage);
    TileMap.graphics.drawTileMap(TileMap.OI1, TileMap.tilesetImage);
    TileMap.graphics.drawTileMap(TileMap.OI2, TileMap.tilesetImage);

}

void CHARACTER_MOVE(Mouse &mouse, Graphics &graphics, SPRITE_CHARACTER &Sprite_Robber){
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

void DRAW_LAYER2(TILEMAP &TileMap, IMAGE &Image){
        SDL_SetTextureAlphaMod(TileMap.tilesetImage, 100);
        TileMap.graphics.drawTileMap(TileMap.Layer2, TileMap.tilesetImage);
        SDL_SetTextureAlphaMod(TileMap.tilesetImage, 255);

        DRAW_CAMERA(TileMap, TileMap.graphics);

        Image.graphics.renderTexture(Image.NightMark, 0, 0);

}

void CHECK_HINT(Mouse &mouse, WALL_OBJECTS_ZONE &woz, IMAGE &Image){
    const Uint8* KeyE = SDL_GetKeyboardState(NULL);
    if(Collision3(mouse, woz.hint)){
        if (KeyE[SDL_SCANCODE_E]){
            Image.graphics.renderTexture(Image.Hint1, 300, 0);
        }
    }
}

void CHECK_DOGCHASE(Mouse &mouse, DOG &dog, IMAGE &Image, ZONE &vcd, BOOL &b){
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
                Image.graphics.render(dog.x, dog.y, dog.DogRun, dog.right);

            }else{
                Image.graphics.renderTexture(Image.DogImage, dog.x, dog.y);

                if(Collision3(mouse, dog)){
                    Image.graphics.renderTexture(Image.Busted, 0, 0);
                    Image.graphics.presentScene();
                    SDL_Delay(3000);

                    b.gamePlay = 0;
                    b.menu = 1;
                }
            }
        }else{
            Image.graphics.renderTexture(Image.SleepDog, 322, 465);
        }
}

void COLLISION_INTERACT(Mouse &mouse, TILEMAP &TileMap, WALL_OBJECTS_ZONE &woz, IMAGE &Image){
    CheckBorder(mouse);
    CheckCollisionWall(mouse, woz.walls);

    const Uint8* Keyy = SDL_GetKeyboardState(NULL);
    CheckCollisionObjects(mouse, woz.objects, Keyy, TileMap);
    CheckCollisionObjectsToRender(mouse, woz.vungchelap, Image.graphics, TileMap);

    CheckCollisionCamera(mouse, woz.camerascan, TileMap.cn);

}

void DOG_INIT(IMAGE &Image, DOG &dog){
    Sprite DogRun;
    DogRun.init(Image.DogRuns, DOGRUN_FRAMES, DOGRUN_CLIPS);
    dog.DogRun = DogRun;
}

void UPDATE_TIME(TIME &GameplayTime, BOOL &b, IMAGE &Image, TTF_Font* font, const SDL_Color &textColor ){
    Uint32 currentTicks = SDL_GetTicks();
    Uint32 deltaTime = currentTicks - GameplayTime.prevTicks;
    GameplayTime.prevTicks = currentTicks;

    GameplayTime.countdownTimer -= deltaTime;

    if (GameplayTime.countdownTimer <= 0) {
        b.gamePlay = false;
        b.menu = true;
    }
    int minutes = static_cast<int>(GameplayTime.countdownTimer / 60000);
    int seconds = static_cast<int>((GameplayTime.countdownTimer - (minutes * 60000)) / 1000);

    string timeStr = to_string(minutes) + ":" + std::to_string(seconds);

    Image.TimeText = Image.graphics.renderText(timeStr.c_str(), font, textColor);
}

void GamePlay(BOOL &b, Graphics &graphics){
    Mouse mouse;

    TILEMAP TileMap;
    TILEMAP_INIT(TileMap, graphics);

    SPRITE_CHARACTER Sprite_Robber;
    SPRITE_CHARACTER_INIT(graphics, Sprite_Robber);

    IMAGE Image;
    IMAGE_INIT(Image, graphics);

    WALL_OBJECTS_ZONE woz;
    WOZ_INIT(woz, graphics);

    DOG dog;
    DOG_INIT(Image, dog);

    SDL_Event event;

    Mix_Music *gMusic = graphics.loadMusic("Music\\sneaky_feet.mp3");
    graphics.play(gMusic);

    TTF_Font* font = graphics.loadFont("font\\VT323-Regular.ttf", 50);
    SDL_Color textColor = {255, 255, 255, 255};

//    double countdownTimer = INITIAL_COUNTDOWN_TIMER;
//    Uint32 prevTicks = SDL_GetTicks();
//
    TIME GameplayTime;

    while(b.gamePlay){
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT){
                b.gamePlay = 0;
                b.quit = 1;
            }
        }
        UPDATE_TIME(GameplayTime, b, Image, font, textColor);

        DRAW_BACKGROUND_OBJECTS(TileMap);

        CHARACTER_MOVE(mouse, graphics, Sprite_Robber);

        COLLISION_INTERACT(mouse, TileMap, woz, Image);

        CHECK_DOGCHASE(mouse, dog, Image, woz.vungchoduoi, b);

        DRAW_LAYER2(TileMap, Image);

        CHECK_HINT(mouse, woz, Image);

        graphics.renderTexture(Image.TimeText, 10, 10);

        graphics.presentScene();

        SDL_Delay(10);

    }

    if (gMusic != nullptr) Mix_FreeMusic( gMusic );

}

int main(int argc, char* argv[])
{
    BOOL b;
    b.quit = 0;
    b.gamePlay = 0;
    b.menu = 1;
    SDL_Event event;

    Graphics graphics;
    graphics.init();

    while (!b.quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) b.quit = true;
        }

        if(b.menu){
            RunMenu(b, graphics);
        }else if(b.gamePlay){
            GamePlay(b, graphics);
        }

    }

    graphics.quit();
    return 0;

}
