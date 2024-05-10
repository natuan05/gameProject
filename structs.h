#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "def.h"
#include "graphics.h"
#include "Objects.h"

struct BOOL{
    bool quit = 0;
    bool gamePlay = 0;
    bool menu = 1;
    bool shop = 0;
};

struct IMAGE{
    Graphics graphics;
    SDL_Texture* SleepDog =  nullptr;
    SDL_Texture* DogImage=  nullptr;
    SDL_Texture* NightMark=  nullptr;
    SDL_Texture* Hint1=  nullptr;
    SDL_Texture* DogRuns=  nullptr;
    SDL_Texture* Busted=  nullptr;
    SDL_Texture* TimeText=  nullptr;
    SDL_Texture* MoneyText =  nullptr;
    SDL_Texture* MissionComplete = nullptr;
    SDL_Texture* Racingcar = nullptr;

    IMAGE(Graphics &graphics) : graphics(graphics) {
        Init();
    }

    ~IMAGE() {
        FreeResources();
    }

    void Init() {
        DogImage = graphics.loadTexture("img\\dog.png");
        Hint1 = graphics.loadTexture("img\\BeCarefulCamera.png");
        NightMark = graphics.loadTexture("img\\night.png");
        SDL_SetTextureAlphaMod(NightMark, 100);
        SleepDog = graphics.loadTexture("img\\sleepdog.png");
        DogRuns = graphics.loadTexture(DOGRUN_SPRITE_FILE);
        Busted = graphics.loadTexture("img\\Busted.png");
        MissionComplete = graphics.loadTexture("img\\Good.png");
        Racingcar = graphics.loadTexture("img\\Racingcar.png");
    }

    void FreeResources();

};

struct SPRITE_CHARACTER{
    Sprite Run;
    Sprite Slow;

    Uint32 prevTicksR= SDL_GetTicks();
    Uint32 prevTicksS= SDL_GetTicks();

    SPRITE_CHARACTER(Graphics &graphics) {
        Init(graphics);
    }

    ~SPRITE_CHARACTER() {
        FreeResources();
    }


    void Init(Graphics &graphics) {
        SDL_Texture* characterRun = graphics.loadTexture(ROBBERRUN_SPRITE_FILE);
        Run.init(characterRun, ROBBERRUN_FRAMES, ROBBERRUN_CLIPS);
        characterRun = nullptr;

        SDL_Texture* characterSlow = graphics.loadTexture(ROBBERSLOW_SPRITE_FILE);
        Slow.init(characterSlow, ROBBERSLOW_FRAMES, ROBBERSLOW_CLIPS);
        characterSlow = nullptr;
    }

    void FreeResources() {
        Run.free();
        Slow.free();
    }
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

    DOG(IMAGE &Image) {
        Init(Image);
    }

    void Init(IMAGE &Image) {
        DogRun.init(Image.DogRuns, DOGRUN_FRAMES, DOGRUN_CLIPS);
    }

    void FreeResources(){
        DogRun.free();
    }
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

    TILEMAP(Graphics &graphics) : graphics(graphics) {
        init();
    }

    void init() {
        tilesetImage = graphics.loadTexture("Map\\tilemap.png");
        OI1 = loadTileMapFromCSV("Map\\gameDemo2_Objects.csv");
        OI2 = loadTileMapFromCSV("Map\\gameDemo2_Objects2.csv");
        OI1CP = OI1;
        OI2CP = OI2;
        BackGround = loadTileMapFromCSV("Map\\gameDemo2_BackGround.csv");
        Camera1 = loadTileMapFromCSV("Map\\gameDemo2_Cam1.csv");
        Camera2 = loadTileMapFromCSV("Map\\gameDemo2_Cam2.csv");
        CameraNow = Camera1;
        Layer2 = loadTileMapFromCSV("Map\\gameDemo2_Layer2.csv");
    }

    void freeResources() {
        if (tilesetImage != nullptr) {
            SDL_DestroyTexture(tilesetImage);
            tilesetImage = nullptr;
        }
    }

};

void IMAGE ::FreeResources() {
    if (SleepDog != nullptr) {
        SDL_DestroyTexture(SleepDog);
        SleepDog = nullptr;
    }
    if (DogImage != nullptr) {
        SDL_DestroyTexture(DogImage);
        DogImage = nullptr;
    }
    if (NightMark != nullptr) {
        SDL_DestroyTexture(NightMark);
        NightMark = nullptr;
    }
    if (Hint1 != nullptr) {
        SDL_DestroyTexture(Hint1);
        Hint1 = nullptr;
    }
    if (DogRuns != nullptr) {
        SDL_DestroyTexture(DogRuns);
        DogRuns = nullptr;
    }
    if (Busted != nullptr) {
        SDL_DestroyTexture(Busted);
        Busted = nullptr;
    }
    if (TimeText != nullptr) {
        SDL_DestroyTexture(TimeText);
        TimeText = nullptr;
    }
    if (MoneyText != nullptr) {
        SDL_DestroyTexture(MoneyText);
        MoneyText = nullptr;
    }
    if (MissionComplete != nullptr) {
        SDL_DestroyTexture(MissionComplete);
        MissionComplete = nullptr;
    }
    if (Racingcar != nullptr){
        SDL_DestroyTexture(Racingcar);
        Racingcar = nullptr;
    }
}
struct MENU_IMAGE{
    Graphics graphics;
    SDL_Texture* MenuBackground =  nullptr;
    SDL_Texture* ButtonMap =  nullptr;
    SDL_Texture* MoneyText  =  nullptr;

    MENU_IMAGE(Graphics &graphics): graphics(graphics) {
        init();
    }
    ~MENU_IMAGE() {
        freeResources();
    }

    void init() {
        MenuBackground = graphics.loadTexture("img\\menubackground.png");
        ButtonMap = graphics.loadTexture("img\\MapButton.png");
    }

    void freeResources() {
        if (MenuBackground != nullptr) {
            SDL_DestroyTexture(MenuBackground);
            MenuBackground = nullptr;
        }
        if (ButtonMap != nullptr) {
            SDL_DestroyTexture(ButtonMap);
            ButtonMap = nullptr;
        }
        if (MoneyText != nullptr) {
            SDL_DestroyTexture(MoneyText);
            MoneyText = nullptr;
        }
    }
};

struct WALL_OBJECTS_ZONE{
    Graphics graphics;
    vector<WALL> walls;
    vector<OBJECTS> objects;
    vector<ZONE> vungchelap;
    vector<ZONE> camerascan;

    ZONE vungchoduoi;
    ZONE hint;
    ZONE GetInCar;


    WALL_OBJECTS_ZONE(Graphics &graphics): graphics(graphics) {
        Init();
    }

    void Init() {
        walls = WallInit();
        objects = ObjectsInit();
        camerascan = CamScanInit();
        vungchelap = VCLInit();
        vungchoduoi = ZONE("vungchoduoi", 320, 0, 320, 737);
        hint = ZONE("hint", 256, 256, 32, 32);
        GetInCar = ZONE("", 128, 64, 32, 32);
    }
};

struct BUTTONS{
    ZONE Bshop;
    ZONE Bmap;

    BUTTONS(){
        ZONE M("Mapbutton", 156, 126, 320, 110);
        ZONE S("Shopbutton", 156, 500, 320, 110);

        Bmap = M;
        Bshop = S;
    }

};

struct TIME{
    double countdownTimer = INITIAL_COUNTDOWN_TIMER;
    Uint32 prevTicks = SDL_GetTicks();
};

struct FONT{
    TTF_Font* font1 =  nullptr;
    SDL_Color textColor;
    FONT(Graphics &graphics) {
        init(graphics);
    }

    ~FONT() {
        freeResources();
    }

    void init(Graphics &graphics) {
        font1 = graphics.loadFont("font\\VT323-Regular.ttf", 40);
        textColor = {255, 255, 255, 255};
    }

    void freeResources() {
        if (font1 != nullptr) {
            TTF_CloseFont(font1);
            font1 = nullptr;
        }
    }
};

struct BAG{
    int money = 0;
    double weight = 0;

};

struct SOUND {
    Graphics graphics;
    Mix_Music *background_music = nullptr;
    Mix_Chunk *dog_barking = nullptr;
    Mix_Chunk *tada = nullptr;
    Mix_Chunk *cash_register = nullptr;

    SOUND(Graphics &graphics) : graphics(graphics) {
        Init();
    }

    ~SOUND() {
        FreeResources();
    }

    void Init() {
        background_music = graphics.loadMusic("Music\\sneaky_feet.mp3");
        dog_barking = graphics.loadSound("Music\\dog_barking.mp3");
        tada = graphics.loadSound("Music\\tada.mp3");
        cash_register = graphics.loadSound("Music\\cash_register.mp3");

        if (dog_barking != nullptr) {
            Mix_VolumeChunk(dog_barking, 30);
        }
    }

    void FreeResources() {
        if (background_music != nullptr) {
            Mix_FreeMusic(background_music);
            background_music = nullptr;
        }
        if (dog_barking != nullptr) {
            Mix_FreeChunk(dog_barking);
            dog_barking = nullptr;
        }
        if (tada != nullptr) {
            Mix_FreeChunk(tada);
            tada = nullptr;
        }
        if (cash_register != nullptr) {
            Mix_FreeChunk(cash_register);
            cash_register = nullptr;
        }
    }
};

struct Car {
    double x, y;
    double speed = 4;


};

#endif // MENU_H_INCLUDED
