#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "def.h"
#include "graphics.h"
#include "Objects.h"


struct BOOL{
    bool quit = 0;
    bool gamePlay1 = 0;
    bool gamePlay2 = 0;
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
    SDL_Texture* Star = nullptr;
    SDL_Texture* Star_bright = nullptr;
    SDL_Texture* Youdied = nullptr;


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
        Star = graphics.loadTexture("img\\star.png");
        Star_bright = graphics.loadTexture("img\\star_bright.png");
        Youdied = graphics.loadTexture("img\\Youdied.png");

    }

    void FreeResources();

};

vector <WALL> WallInit(const BOOL &b){
    vector <WALL> walls;
    walls.emplace_back(640, 416, 32, 288);
    walls.emplace_back(1216, 64, 32, 640);
    walls.emplace_back(640, 64, 608, 32);
    walls.emplace_back(640, 64, 32, 256);
    walls.emplace_back(896, 64, 32, 256);
    walls.emplace_back(896, 288, 160, 32);
    walls.emplace_back(832, 416, 224, 32);
    walls.emplace_back(960, 512, 32, 192);
    walls.emplace_back(832, 544, 160, 32);
    walls.emplace_back(960, 416, 32, 64);
    walls.emplace_back(288, 416, 32, 320);
    walls.emplace_back(288, 0, 32, 320);
    walls.emplace_back(640, 672, 608, 32);
    walls.emplace_back(832, 608, 32, 96);
    walls.emplace_back(832, 416, 32, 160);
    walls.emplace_back(1088, 288, 160, 32);
    walls.emplace_back(1088, 416, 160, 32);
    if (b.gamePlay2){
        walls.emplace_back(352, 32, 32, 64);
        walls.emplace_back(416, 32, 128, 32);
        walls.emplace_back(576, 32, 32, 192);
        walls.emplace_back(480, 96, 32, 32);
        walls.emplace_back(512, 128, 32, 32);
        walls.emplace_back(416, 96, 32, 128);
        walls.emplace_back(352, 128, 96, 32);
        walls.emplace_back(480, 192, 64, 32);
        walls.emplace_back(512, 192, 32, 64);
        walls.emplace_back(352, 192, 32, 160);
        walls.emplace_back(352, 288, 96, 32);
        walls.emplace_back(416, 256, 96, 32);
        walls.emplace_back(576, 256, 32, 64);
        walls.emplace_back(544, 288, 32, 64);
        walls.emplace_back(448, 320, 96, 32);
        walls.emplace_back(320, 384, 64, 32);
        walls.emplace_back(416, 384, 64, 32);
        walls.emplace_back(512, 352, 32, 64);
        walls.emplace_back(512, 384, 96, 32);
        walls.emplace_back(576, 384, 32, 128);
        walls.emplace_back(416, 448, 64, 32);
        walls.emplace_back(448, 448, 32, 96);
        walls.emplace_back(320, 480, 64, 32);
        walls.emplace_back(352, 544, 32, 128);
        walls.emplace_back(416, 544, 32, 32);
        walls.emplace_back(416, 608, 128, 32);
        walls.emplace_back(512, 576, 32, 64);
        walls.emplace_back(576, 544, 32, 128);
        walls.emplace_back(512, 448, 32, 96);
        walls.emplace_back(448, 608, 32, 96);
        walls.emplace_back(512, 672, 32, 64);
        walls.emplace_back(512, 704, 64, 32);
        walls.emplace_back(352, 704, 64, 32);
    }

    // Return the constructed vector
    return walls;

}

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

struct Node {
    int x, y;
    double gCost, hCost, fCost;
    Node* parent;

    Node() : x(0), y(0), gCost(0), hCost(0), fCost(0), parent(nullptr) {}


    Node(int x, int y, double gCost = 0, double hCost = 0, Node* parent = nullptr)
        : x(x), y(y), gCost(gCost), hCost(hCost), parent(parent) {
        fCost = gCost + hCost;
    }

    bool operator>(const Node& other) const {
        return fCost > other.fCost;
    }
};
struct DOG {
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

    vector<Node> path;
    size_t pathIndex = 0;

    DOG(IMAGE &Image) {
        Init(Image);
    }

    void Init(IMAGE &Image) {
        DogRun.init(Image.DogRuns, DOGRUN_FRAMES, DOGRUN_CLIPS);
    }

    void FreeResources() {
        DogRun.free();
    }

    vector<Node> findPath(int startX, int startY, int goalX, int goalY, const vector<vector<int>>& grid);
};


struct TILEMAP{
    Graphics graphics;
    SDL_Texture* tilesetImage;
    vector<vector<int>> OI1;
    vector<vector<int>> OI1CP;
    vector<vector<int>> OI2;
    vector<vector<int>> OI2CP;
    vector<vector<int>> mapdog;


    vector<vector<int>> BackGround;
    vector<vector<int>> Layer2;

    vector<vector<int>> Camera1;
    vector<vector<int>> Camera2;
    vector<vector<int>> CameraNow;
    Uint32 prevTicksForCam = SDL_GetTicks();
    bool cn = 1;

    TILEMAP(Graphics &graphics, BOOL &b) : graphics(graphics) {
        init(b);
    }

    void init(const BOOL &b) {

            tilesetImage = graphics.loadTexture("Map\\tilemap.png");
            if (b.gamePlay2){
                OI1 = LoadTileMapFromCSV("Map2\\gameDemo2_Objects.csv");
            }else{
                OI1 = LoadTileMapFromCSV("Map\\gameDemo2_Objects.csv");
            }

            OI2 = LoadTileMapFromCSV("Map\\gameDemo2_Objects2.csv");

            OI1CP = OI1;
            OI2CP = OI2;
            BackGround = LoadTileMapFromCSV("Map\\gameDemo2_BackGround.csv");
            Camera1 = LoadTileMapFromCSV("Map\\gameDemo2_Cam1.csv");
            Camera2 = LoadTileMapFromCSV("Map\\gameDemo2_Cam2.csv");
            CameraNow = Camera1;
            Layer2 = LoadTileMapFromCSV("Map\\gameDemo2_Layer2.csv");

            mapdog = ConvertTileMapToBinary(OI1);

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
    if (Star_bright != nullptr){
        SDL_DestroyTexture(Star_bright);
        Star_bright = nullptr;
    }
    if (Star != nullptr){
        SDL_DestroyTexture(Star);
        Star = nullptr;
    }
    if (Youdied != nullptr){
        SDL_DestroyTexture(Youdied);
        Youdied = nullptr;
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
    ZONE Road;


    WALL_OBJECTS_ZONE(Graphics &graphics, const BOOL &b): graphics(graphics) {
        Init(b);
    }

    void Init(const BOOL &b) {
        walls = WallInit(b);
        objects = ObjectsInit();
        camerascan = CamScanInit();
        vungchelap = VCLInit();
        vungchoduoi = ZONE("vungchoduoi", 320, 0, 320, 737);
        hint = ZONE("hint", 256, 256, 32, 32);
        GetInCar = ZONE("", 128, 64, 32, 32);
        Road = ZONE("", 0, 0, 224, 736);
    }
};

struct BUTTONS{
    ZONE Bmap2;
    ZONE Bmap;

    BUTTONS(){
        ZONE M("Mapbutton", 156, 126, 320, 110);
        ZONE S("Shopbutton", 156, 310, 320, 110);

        Bmap = M;
        Bmap2 = S;
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
    Mix_Chunk *car_accident = nullptr;
    Mix_Chunk *fail = nullptr;
    Mix_Chunk *horn = nullptr;

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
        car_accident = graphics.loadSound("Music\\car_accident.mp3");
        fail = graphics.loadSound("Music\\fail.mp3");
        horn = graphics.loadSound("Music\\horn.mp3");

        Mix_VolumeChunk(dog_barking, 30);
        Mix_VolumeChunk(horn, 30);

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
    SDL_Rect position = {64, -128, 80, 128};

    double speed = 7;
    bool isrunning = 0;

    void Update(){
        position.y += speed;
        if (position.y > SCREEN_HEIGHT){
                isrunning = 0;
        }
    }

    void Render(IMAGE &Image){
        Image.graphics.renderTexture(Image.Racingcar, position.x, position.y);
    }

    void Randomcar(SOUND &gameSound){
        if (!isrunning){
            int num = rand() % 130;
            if ( num == 50 ){
                isrunning = 1;
                position.x = 64;
                position.y = -128;
            }
        }else{
            gameSound.graphics.play(gameSound.horn);
            Update();

        }
    }

};



#endif // MENU_H_INCLUDED
