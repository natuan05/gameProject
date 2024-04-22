#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include "def.h"


using namespace std;

struct Sprite {
    SDL_Texture* texture;
    std::vector<SDL_Rect> clips;
    int currentFrame = 0;

    void init(SDL_Texture* _texture, int frames, const int _clips [][4]) {
        texture = _texture;
        SDL_Rect clip;
        for (int i = 0; i < frames; i++) {
            clip.x = _clips[i][0];
            clip.y = _clips[i][1];
            clip.w = _clips[i][2];
            clip.h = _clips[i][3];

            clips.push_back(clip);
        }
    }
    void tick(Uint32& prevTicks) {
        Uint32 currentTicks = SDL_GetTicks();
        Uint32 deltaTicks = currentTicks - prevTicks;

        if (deltaTicks >= MS_PER_FRAME){
            currentFrame = (currentFrame + 1) % clips.size();
            prevTicks = currentTicks;
        }

    }

    const SDL_Rect* getCurrentClip() const {
        return &(clips[currentFrame]);
    }
};

struct Graphics{
    SDL_Renderer* renderer;
    SDL_Window* window;

    void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "%s: %s", msg, error);
        SDL_Quit();
    }

    void init() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                   SDL_WINDOW_SHOWN);
        if (window == nullptr)
                   logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1,
                     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        //renderer =
                  SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr)
             logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    void prepareScene(SDL_Texture * background)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy( renderer, background, NULL, NULL);
    }

    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }

    SDL_Texture *loadTexture(const char *filename)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Loading %s", filename);
        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                  SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }


     void render(int x, int y, const Sprite& sprite, bool goR) {
        const SDL_Rect* clip = sprite.getCurrentClip();
        SDL_Rect renderQuad = {x, y, clip->w, clip->h};
        SDL_RendererFlip flip = (goR) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(renderer, sprite.texture, clip, &renderQuad, 0, nullptr, flip);

    }

    void renderTile(int x, int y, int tileID, SDL_Texture* tilesetImage) {
        SDL_Rect dest;
        SDL_QueryTexture(tilesetImage, nullptr, nullptr, &dest.w, &dest.h);

        int TILESET_NUM_COLS= dest.w/ TILE_WIDTH;
        // Tính toán tọa độ trong tileset của tile tương ứng
        int tilesetX = (tileID % TILESET_NUM_COLS) * TILE_WIDTH;
        int tilesetY = (tileID / TILESET_NUM_COLS) * TILE_HEIGHT;

        // Tạo hình chữ nhật (SDL_Rect) cho vị trí và kích thước của tile trong tileset
        SDL_Rect srcRect = {tilesetX, tilesetY, TILE_WIDTH, TILE_HEIGHT};

        // Tạo hình chữ nhật (SDL_Rect) cho vị trí và kích thước của tile trên màn hình
        SDL_Rect destRect = {x, y, TILE_WIDTH, TILE_HEIGHT};

        // Vẽ tile lên màn hình
        SDL_RenderCopy(renderer, tilesetImage, &srcRect, &destRect);
    }

    void drawTileMap(const vector<vector<int>>& tileMap, SDL_Texture* tilesetImage) {
        // Vẽ từng tile trong tile map
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int x = 0; x < MAP_WIDTH; ++x) {
                int tileID = tileMap[y][x];
                renderTile(x * TILE_WIDTH, y * TILE_HEIGHT, tileID, tilesetImage);
            }
        }
    }

    void drawCamera(const vector<vector<int>> &Cam1, const vector<vector<int>> &Cam2, vector<vector<int>> &CamNow, Uint32 &prevTicks, SDL_Texture* tilesetImage, bool &camnow){
        Uint32 currentTicks = SDL_GetTicks();
        Uint32 deltaTicks = currentTicks - prevTicks;

        if (deltaTicks >= MS_PER_CAMERA){
            CamNow= (CamNow == Cam1) ? Cam2 : Cam1;
            camnow= (CamNow == Cam1) ? 1 : 0;
            prevTicks = currentTicks;
        }

        drawTileMap(CamNow, tilesetImage);
    }

    void quit()
    {
        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};


#endif // GRAPHICS__H


