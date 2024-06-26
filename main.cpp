#include "def.h"
#include "graphics.h"
#include "game.h"
#include "Map.h"
#include "Objects.h"
#include "structs.h"
#include "menu_processing.h"

using namespace std;
void SaveBag(const BAG &bagMenu) {
    ofstream outFile("bag_menu.txt", ios::trunc);
    if (outFile.is_open()) {
        outFile << bagMenu.money << "\n";
        outFile.close();
    } else {
        cout << "khong mo duoc savebag" << endl;
    }
}
void Draw_Menu(MENU_IMAGE &MImage){
    SDL_RenderClear(MImage.graphics.renderer);
    MImage.graphics.renderTexture(MImage.MenuBackground, 0, 0);

}

void Draw_Background_Objects(TILEMAP &TileMap){
    SDL_RenderClear(TileMap.graphics.renderer);
    TileMap.graphics.drawTileMap(TileMap.BackGround, TileMap.tilesetImage);
    TileMap.graphics.drawTileMap(TileMap.OI1, TileMap.tilesetImage);
    TileMap.graphics.drawTileMap(TileMap.OI2, TileMap.tilesetImage);
}

void DxDy_Weight(Mouse &mouse, BAG &Bag){
    if (mouse.dx > 0.5){
        if (mouse.dx - Bag.weight > 0.5){
            mouse.dx -= Bag.weight;
        }else{
            mouse.dx = 0.5;
        }
    }else if (mouse.dx < -0.5){
        if (mouse.dx + Bag.weight < -0.5){
            mouse.dx += Bag.weight;
        }else{
            mouse.dx = -0.5;
        }
    }

    if (mouse.dy > 0){
        if (mouse.dy - Bag.weight > 0.5){
            mouse.dy -= Bag.weight;
        }else{
            mouse.dy = 0.5;
        }
    }else if (mouse.dy < 0){
        if (mouse.dy + Bag.weight < -0.5){
            mouse.dy += Bag.weight;
        }else{
            mouse.dy = -0.5;
        }
    }
}

void Character_Move(Mouse &mouse, Graphics &graphics, SPRITE_CHARACTER &Sprite_Robber, BAG &Bag){
        mouse.UpdateDxDy();
        if (mouse.isMoving()) {
            Sprite_Robber.Run.tick(Sprite_Robber.prevTicksR);
            Sprite_Robber.Slow.tick(Sprite_Robber.prevTicksS);
        }

        DxDy_Weight(mouse, Bag);

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

void Draw_Camera(TILEMAP &TileMap, Graphics &graphics){
        Uint32 currentTicks = SDL_GetTicks();
        Uint32 deltaTicks = currentTicks - TileMap.prevTicksForCam;

        if (deltaTicks >= MS_PER_CAMERA){
            TileMap.CameraNow= (TileMap.CameraNow == TileMap.Camera1) ? TileMap.Camera2 : TileMap.Camera1;
            TileMap.cn= (TileMap.CameraNow == TileMap.Camera1) ? 1 : 0;
            TileMap.prevTicksForCam = currentTicks;
        }

        graphics.drawTileMap(TileMap.CameraNow, TileMap.tilesetImage);

}

void Draw_Layer2(TILEMAP &TileMap, IMAGE &Image){


    SDL_SetTextureAlphaMod(TileMap.tilesetImage, 100);
    TileMap.graphics.drawTileMap(TileMap.Layer2, TileMap.tilesetImage);
    SDL_SetTextureAlphaMod(TileMap.tilesetImage, 255);

    Draw_Camera(TileMap, TileMap.graphics);

    Image.graphics.renderTexture(Image.NightMark, 0, 0);

}

void Check_Hint(const Mouse &mouse,const WALL_OBJECTS_ZONE &woz, IMAGE &Image){
    const Uint8* KeyE = SDL_GetKeyboardState(NULL);
    if(Collision3(mouse, woz.hint)){
        if (KeyE[SDL_SCANCODE_E]){
            Image.graphics.renderTexture(Image.Hint1, 300, 0);
        }
    }

}

void Escape(Mouse &mouse,const WALL_OBJECTS_ZONE &woz, IMAGE &Image, BOOL &b, SOUND &gameSound, BAG &Bag, BAG &Bag_Menu){
    const Uint8* KeyE = SDL_GetKeyboardState(NULL);
    if(Collision3(mouse, woz.GetInCar)){
        if (KeyE[SDL_SCANCODE_E]){
            Bag_Menu.money += Bag.money;
            SaveBag(Bag_Menu);
            Image.graphics.renderTexture(Image.MissionComplete, 0, 0);

            if (Bag.money < 1000){
                Image.graphics.renderTexture(Image.Star, 0, 0);
                Image.graphics.renderTexture(Image.Star, 180, 0);
                Image.graphics.renderTexture(Image.Star, 360, 0);
            }else if (Bag.money < 2250){
                Image.graphics.renderTexture(Image.Star_bright, 0, 0);
                Image.graphics.renderTexture(Image.Star, 180, 0);
                Image.graphics.renderTexture(Image.Star, 360, 0);
            }else if (Bag.money < 3000){
                Image.graphics.renderTexture(Image.Star_bright, 0, 0);
                Image.graphics.renderTexture(Image.Star_bright, 180, 0);
                Image.graphics.renderTexture(Image.Star, 360, 0);
            }else{
                Image.graphics.renderTexture(Image.Star_bright, 0, 0);
                Image.graphics.renderTexture(Image.Star_bright, 180, 0);
                Image.graphics.renderTexture(Image.Star_bright, 360, 0);
            }

            Image.graphics.presentScene();

            if (gameSound.dog_barking != nullptr) {
                Mix_FreeChunk(gameSound.dog_barking);
                gameSound.dog_barking = nullptr;
            }
            Mix_FreeMusic(gameSound.background_music);
            gameSound.background_music = nullptr;

            Image.graphics.play(gameSound.tada);

            SDL_Delay(3000);
            b.menu = 1;
            b.gamePlay1 = 0;
        }
    }
}

void Check_Dogchase(Mouse &mouse, DOG &dog, IMAGE &Image, ZONE &vcd, BOOL &b, SOUND &gameSound, TILEMAP &TileMap){
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
                updateDogPosition(mouse, dog, TileMap.mapdog);
                Image.graphics.render(dog.x, dog.y, dog.DogRun, dog.right);
                Image.graphics.play(gameSound.dog_barking);

            }else{
                Image.graphics.renderTexture(Image.DogImage, dog.x, dog.y);
                if(Collision3(mouse, dog)){
                    Busted_Out(Image, b, gameSound);
                }
            }
        }else{
            Image.graphics.renderTexture(Image.SleepDog, 322, 465);
        }
}

void Collision_Interact(Mouse &mouse, TILEMAP &TileMap, WALL_OBJECTS_ZONE &woz, IMAGE &Image, BAG &Bag, BOOL &b, SOUND &gameSound){
    CheckBorder(mouse);
    CheckCollisionWall(mouse, woz.walls);

    CheckCollisionObjects(mouse, woz.objects, TileMap, Bag, gameSound);
    CheckCollisionObjectsToRender(mouse, woz.vungchelap, Image.graphics, TileMap);

    CheckCollisionCamera(mouse, woz.camerascan, TileMap.cn, Image, b, gameSound);

}

void Update_Time(TIME &GameplayTime, BOOL &b, IMAGE &Image, TTF_Font* font, const SDL_Color &textColor ){
    Uint32 currentTicks = SDL_GetTicks();
    Uint32 deltaTime = currentTicks - GameplayTime.prevTicks;
    GameplayTime.prevTicks = currentTicks;

    GameplayTime.countdownTimer -= deltaTime;

    if (GameplayTime.countdownTimer <= 0) {
        b.gamePlay1 = false;
        b.menu = true;
    }
    int minutes = static_cast<int>(GameplayTime.countdownTimer / 60000);
    int seconds = static_cast<int>((GameplayTime.countdownTimer - (minutes * 60000)) / 1000);

    string timeStr = to_string(minutes) + ":" + std::to_string(seconds);
    SDL_DestroyTexture(Image.TimeText);
    Image.TimeText = Image.graphics.renderText(timeStr.c_str(), font, textColor);
}

void Render_Text(IMAGE &Image, BAG &Bag, FONT &Font){
    Image.graphics.renderTexture(Image.TimeText, 10, 10);

    string moneyStr = "$:" + to_string(Bag.money);
    SDL_DestroyTexture(Image.MoneyText);
    Image.MoneyText = Image.graphics.renderText(moneyStr.c_str(), Font.font1, Font.textColor);
    Image.graphics.renderTexture(Image.MoneyText, 10, 60);

}

void Render_Menutext(MENU_IMAGE &MImage, BAG &Bag_Menu, FONT &Font){
    string moneyStr = "$:" + to_string(Bag_Menu.money);
    SDL_DestroyTexture(MImage.MoneyText);
    MImage.MoneyText = MImage.graphics.renderText(moneyStr.c_str(), Font.font1, Font.textColor);
    MImage.graphics.renderTexture(MImage.MoneyText, 10, 10);
}

void LoadBag(BAG &Bag_Menu) {
    ifstream inFile("bag_menu.txt");
    if (inFile.is_open()) {
        inFile >> Bag_Menu.money;
        inFile.close();
    } else {
        cout << "khong mo duoc";
    }
}


void RunMenu(BOOL &b, Graphics &graphics, FONT &Font, BAG &Bag_Menu){
    LoadBag(Bag_Menu);
    MENU_IMAGE MImage(graphics);
    BUTTONS Buttons;

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

        Draw_Menu(MImage);
        Render_Menutext(MImage, Bag_Menu, Font);

        graphics.presentScene();


        SDL_Delay(10);
    }

    MImage.freeResources();
    if (gMusic != nullptr) Mix_FreeMusic( gMusic );
}

void CheckCar(Car &QuangCar, IMAGE &Image, Mouse &mouse, BOOL &b, SOUND &gameSound, BAG &Bag_Menu, WALL_OBJECTS_ZONE &woz){
    if (Collision3(mouse, woz.Road)){
        QuangCar.Randomcar(gameSound);
        QuangCar.Render(Image);
        if (CollisionWithCar(mouse, QuangCar.position)){
            Image.graphics.renderTexture(Image.Youdied, 0, 0);
            Image.graphics.presentScene();
            if (gameSound.dog_barking != nullptr) {
                Mix_FreeChunk(gameSound.dog_barking);
                gameSound.dog_barking = nullptr;
            }
            Mix_FreeChunk(gameSound.horn);
            gameSound.horn = nullptr;

            Mix_FreeMusic(gameSound.background_music);
            gameSound.background_music = nullptr;

            Image.graphics.play(gameSound.car_accident);

            SDL_Delay(3000);

            Bag_Menu.money = 0;
            SaveBag(Bag_Menu);
            b.gamePlay1 = 0;
            b.menu = 1;
        }
    }else{
        if (QuangCar.isrunning){
            QuangCar.Update();
            QuangCar.Render(Image);
        }
    }

}

void GamePlay1(BOOL &b, Graphics &graphics, FONT &Font, BAG &Bag_Menu){
    Mouse mouse;
    TILEMAP TileMap(graphics, b);

    SPRITE_CHARACTER Sprite_Robber(graphics);
    IMAGE Image(graphics);
    SOUND gameSound(graphics);
    WALL_OBJECTS_ZONE woz(graphics, b);
    DOG dog(Image);
    TIME GameplayTime;
    BAG Bag;

    Car QuangCar;

    gameSound.graphics.play(gameSound.background_music);
    SDL_Event event;
    while(b.gamePlay1){
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT){
                b.gamePlay1 = 0;
                b.quit = 1;
            }
        }
        Update_Time(GameplayTime, b, Image, Font.font1, Font.textColor);
        Draw_Background_Objects(TileMap);
        CheckCar(QuangCar, Image, mouse, b, gameSound, Bag_Menu, woz);
        Character_Move(mouse, graphics, Sprite_Robber, Bag);
        Collision_Interact(mouse, TileMap, woz, Image, Bag, b, gameSound);
        Check_Dogchase(mouse, dog, Image, woz.vungchoduoi, b, gameSound, TileMap);
        Draw_Layer2(TileMap, Image);
        Check_Hint(mouse, woz, Image);
        Escape(mouse, woz, Image, b, gameSound, Bag, Bag_Menu);
        Render_Text(Image, Bag, Font);
        graphics.presentScene();
        SDL_Delay(10);

    }

    gameSound.FreeResources();
    Image.FreeResources();
    TileMap.freeResources();
    Sprite_Robber.FreeResources();
    dog.FreeResources();
}
void GamePlay2(BOOL &b, Graphics &graphics, FONT &Font, BAG &Bag_Menu){
    Mouse mouse;
    TILEMAP TileMap(graphics, b);

    SPRITE_CHARACTER Sprite_Robber(graphics);
    IMAGE Image(graphics);
    SOUND gameSound(graphics);
    WALL_OBJECTS_ZONE woz(graphics, b);
    DOG dog(Image);
    DOG dog2(Image);
    TIME GameplayTime;
    BAG Bag;

    Car QuangCar;

    gameSound.graphics.play(gameSound.background_music);
    SDL_Event event;
    while(b.gamePlay2){
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT){
                b.gamePlay1 = 0;
                b.quit = 1;
            }
        }
        Update_Time(GameplayTime, b, Image, Font.font1, Font.textColor);
        Draw_Background_Objects(TileMap);
        CheckCar(QuangCar, Image, mouse, b, gameSound, Bag_Menu, woz);
        Character_Move(mouse, graphics, Sprite_Robber, Bag);
        Collision_Interact(mouse, TileMap, woz, Image, Bag, b, gameSound);
        Check_Dogchase(mouse, dog, Image, woz.vungchoduoi, b, gameSound, TileMap);
        Check_Dogchase(mouse, dog2, Image, woz.vungchoduoi, b, gameSound, TileMap);
        Draw_Layer2(TileMap, Image);
        Check_Hint(mouse, woz, Image);
        Escape(mouse, woz, Image, b, gameSound, Bag, Bag_Menu);
        Render_Text(Image, Bag, Font);
        graphics.presentScene();
        SDL_Delay(10);

    }

    gameSound.FreeResources();
    Image.FreeResources();
    TileMap.freeResources();
    Sprite_Robber.FreeResources();
    dog.FreeResources();
}


int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();
    BOOL b;
    FONT Font(graphics);
    BAG Bag_Menu;
    SDL_Event event;
    while (!b.quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) b.quit = true;
        }

        if(b.menu){
            RunMenu(b, graphics, Font, Bag_Menu);
        }else if(b.gamePlay1){
            GamePlay1(b, graphics, Font, Bag_Menu);
        }else if(b.gamePlay2){
            GamePlay2(b, graphics, Font, Bag_Menu);
        }

    }

    Font.freeResources();

    graphics.quit();
    return 0;

}
