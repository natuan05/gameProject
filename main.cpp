#include "def.h"
#include "graphics.h"
#include "game.h"
#include "Map.h"
#include "Objects.h"
#include "structs.h"
#include "menu_processing.h"

using namespace std;

void MENU_IMAGE_INIT(Graphics &graphics, MENU_IMAGE &MImage){
    SDL_Texture* menubackground = graphics.loadTexture("img\\menubackground.png");
    SDL_Texture* ButtonMap = graphics.loadTexture("img\\MapButton.png");

    MImage.graphics = graphics;
    MImage.MenuBackground = menubackground;
    MImage.ButtonMap = ButtonMap;

}

void DRAW_MENU(MENU_IMAGE &MImage){
    SDL_RenderClear(MImage.graphics.renderer);
    MImage.graphics.renderTexture(MImage.MenuBackground, 0, 0);

}


void TILEMAP_INIT(TILEMAP &TileMap, Graphics &graphics){
    SDL_Texture* tilesetImage= graphics.loadTexture("Map\\tilemap.png");
    vector<vector<int>> BackGround = loadTileMapFromCSV("Map\\gameDemo2_BackGround.csv");
    vector<vector<int>> Layer2 = loadTileMapFromCSV("Map\\gameDemo2_Layer2.csv");
    vector<vector<int>> ObjectsTile1 = loadTileMapFromCSV("Map\\gameDemo2_Objects.csv");
    vector<vector<int>> ObjectsTile2 = loadTileMapFromCSV("Map\\gameDemo2_Objects2.csv");

    vector<vector<int>> Camera1 = loadTileMapFromCSV("Map\\gameDemo2_Cam1.csv");
    vector<vector<int>> Camera2 = loadTileMapFromCSV("Map\\gameDemo2_Cam2.csv");
    vector<vector<int>> CamNow = Camera1;

    TileMap.graphics = graphics;
    TileMap.init(tilesetImage, ObjectsTile1, ObjectsTile2);
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
    SDL_Texture* mc = graphics.loadTexture("img\\Good.png");

    Image.graphics = graphics;
    Image.DogImage = dogimage;
    Image.Hint1 = HintImage;
    Image.NightMark = nightImage;
    Image.SleepDog = sleepdog;
    Image.DogRuns = dogruns;
    Image.Busted = Busted;
    Image.MissionComplete = mc;
}

void WOZ_INIT(WALL_OBJECTS_ZONE &woz, Graphics &graphics){
    vector<WALL> walls = WallInit();
    vector<OBJECTS> objects= ObjectsInit();
    vector<ZONE> camerascan = CamScanInit();
    vector<ZONE> vungchelap = VCLInit();
    ZONE vcd("vungchoduoi", 320, 0, 320, 737);
    ZONE hint("hint", 256, 256, 32, 32);
    ZONE GetInCar("", 128, 64, 32, 32);

    woz.GetInCar = GetInCar;
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

void SOUND_DELETE(SOUND &gameSound){
    Mix_FreeMusic(gameSound.background_music);
    Mix_FreeChunk(gameSound.dog_barking);
}

void CHECK_HINT(Mouse &mouse, WALL_OBJECTS_ZONE &woz, IMAGE &Image){
    const Uint8* KeyE = SDL_GetKeyboardState(NULL);
    if(Collision3(mouse, woz.hint)){
        if (KeyE[SDL_SCANCODE_E]){
            Image.graphics.renderTexture(Image.Hint1, 300, 0);
        }
    }

}

void _ESCAPE(Mouse &mouse, WALL_OBJECTS_ZONE &woz, IMAGE &Image, BOOL &b, SOUND &gameSound, BAG &Bag, BAG &Bag_Menu){
    const Uint8* KeyE = SDL_GetKeyboardState(NULL);
    if(Collision3(mouse, woz.GetInCar)){
        if (KeyE[SDL_SCANCODE_E]){
            Bag_Menu.money += Bag.money;

            Image.graphics.renderTexture(Image.MissionComplete, 0, 0);
            Image.graphics.presentScene();
            Image.graphics.play(gameSound.tada);

            SDL_Delay(1000);
            b.menu = 1;
            b.gamePlay = 0;
        }
    }
}


void CHECK_DOGCHASE(Mouse &mouse, DOG &dog, IMAGE &Image, ZONE &vcd, BOOL &b, Mix_Chunk* g){
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
                Image.graphics.play(g);

            }else{
                Image.graphics.renderTexture(Image.DogImage, dog.x, dog.y);

                if(Collision3(mouse, dog)){
                    Busted_Out(Image, b);
                }
            }
        }else{
            Image.graphics.renderTexture(Image.SleepDog, 322, 465);
        }
}

void COLLISION_INTERACT(Mouse &mouse, TILEMAP &TileMap, WALL_OBJECTS_ZONE &woz, IMAGE &Image, BAG &Bag, BOOL &b){
    CheckBorder(mouse);
    CheckCollisionWall(mouse, woz.walls);

    CheckCollisionObjects(mouse, woz.objects, TileMap, Bag);
    CheckCollisionObjectsToRender(mouse, woz.vungchelap, Image.graphics, TileMap);

    CheckCollisionCamera(mouse, woz.camerascan, TileMap.cn, Image, b);

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

void SOUND_INIT(SOUND &gameSound, Graphics& graphics){
    Mix_Music *background_music = graphics.loadMusic("Music\\sneaky_feet.mp3");
    Mix_Chunk *dog_barking = graphics.loadSound("Music\\dog_barking.mp3");
    Mix_VolumeChunk(dog_barking, 30);
    Mix_Chunk *tada = graphics.loadSound("Music\\tada.mp3");
    Mix_Chunk *cr = graphics.loadSound("Music\\cash_register.mp3");

    gameSound.graphics = graphics;
    gameSound.background_music = background_music;
    gameSound.dog_barking = dog_barking;
    gameSound.tada = tada;
    gameSound.cash_register = cr;
}


void RENDER_TEXT(IMAGE &Image, BAG &Bag, FONT &Font){
    Image.graphics.renderTexture(Image.TimeText, 10, 10);

    string moneyStr = "$:" + to_string(Bag.money);
    Image.MoneyText = Image.graphics.renderText(moneyStr.c_str(), Font.font1, Font.textColor);
    Image.graphics.renderTexture(Image.MoneyText, 10, 60);
}

void RunMenu(BOOL &b, Graphics &graphics, FONT &Font, BAG &Bag_Menu){
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

        string moneyStr = "$:" + to_string(Bag_Menu.money);
        MImage.MoneyText = MImage.graphics.renderText(moneyStr.c_str(), Font.font1, Font.textColor);
        graphics.renderTexture(MImage.MoneyText, 10, 10);

        graphics.presentScene();


        SDL_Delay(10);
    }
    if (gMusic != nullptr) Mix_FreeMusic( gMusic );
}

void GamePlay(BOOL &b, Graphics &graphics, FONT &Font, BAG &Bag_Menu){
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

    SOUND gameSound;
    SOUND_INIT(gameSound, graphics);

    gameSound.graphics.play(gameSound.background_music);

    TIME GameplayTime;

    BAG Bag;

    while(b.gamePlay){
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT){
                b.gamePlay = 0;
                b.quit = 1;
            }
        }
        UPDATE_TIME(GameplayTime, b, Image, Font.font1, Font.textColor);

        DRAW_BACKGROUND_OBJECTS(TileMap);

        CHARACTER_MOVE(mouse, graphics, Sprite_Robber);

        COLLISION_INTERACT(mouse, TileMap, woz, Image, Bag, b);

        CHECK_DOGCHASE(mouse, dog, Image, woz.vungchoduoi, b, gameSound.dog_barking);

        DRAW_LAYER2(TileMap, Image);

        CHECK_HINT(mouse, woz, Image);

        _ESCAPE(mouse, woz, Image, b, gameSound, Bag, Bag_Menu);

        RENDER_TEXT(Image, Bag, Font);

        graphics.presentScene();

        SDL_Delay(10);

    }

    SOUND_DELETE(gameSound);


}

void FONT_INIT(FONT &Font, Graphics &graphics){
    Font.font1 = graphics.loadFont("font\\VT323-Regular.ttf", 40);
    Font.textColor = {255, 255, 255, 255};
}

int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();

    BOOL b;
    b.quit = 0;
    b.gamePlay = 0;
    b.menu = 1;

    FONT Font;
    FONT_INIT(Font, graphics);

    BAG Bag_Menu;

    SDL_Event event;


    while (!b.quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) b.quit = true;
        }

        if(b.menu){
            RunMenu(b, graphics, Font, Bag_Menu);
        }else if(b.gamePlay){
            GamePlay(b, graphics, Font, Bag_Menu);
        }

    }

    graphics.quit();
    return 0;

}
