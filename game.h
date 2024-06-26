
#ifndef GAME_H
#define GAME_H


#include "Objects.h"
#include "Interact.h"
#include "graphics.h"
#include "structs.h"

struct Mouse {

    double x=   START_X;
    double y=  START_Y;

    double dx = 0, dy = 0;
    double speed = INITIAL_SPEED;

    bool right = 1;


    void move() {
        x += dx;
        y += dy;
        dx = 0;
        dy= 0;
    }

    void turnNorth() {
        dy = -speed;
        dx = 0;
    }
    void turnSouth() {
        dy = speed;
        dx = 0;
    }
    void turnWest() {
        dy = 0;
        dx = -speed;
    }
    void turnEast() {
        dy = 0;
        dx = speed;
    }
    void stop(){
        dx = 0;
        dy = 0;
    }

    bool isMoving() {
        return (dx != 0 || dy != 0);
    }

    void UpdateDxDy();


};
void Mouse::UpdateDxDy(){
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

    if (currentKeyStates[SDL_SCANCODE_S]) turnSouth();
    if (currentKeyStates[SDL_SCANCODE_W]) turnNorth();
    if (currentKeyStates[SDL_SCANCODE_A]) turnWest();
    if (currentKeyStates[SDL_SCANCODE_D]) turnEast();

    const int directions[][2] = {
        {SDL_SCANCODE_W, SDL_SCANCODE_A},
        {SDL_SCANCODE_W, SDL_SCANCODE_D},
        {SDL_SCANCODE_S, SDL_SCANCODE_D},
        {SDL_SCANCODE_S, SDL_SCANCODE_A},

    };

    for (const auto& dir : directions) {
        bool allPressed = true;
        for (const auto& key : dir) {
            if (!currentKeyStates[key]) {
                allPressed = false;
                break;
            }
        }

        if (allPressed) {
            dx = (dir[1] == SDL_SCANCODE_A) ? -speed/(sqrt(2)) : speed/(sqrt(2));
            dy = (dir[0] == SDL_SCANCODE_W) ? -speed/(sqrt(2)) : speed/(sqrt(2));
            break;
        }
    }

    if (dx > 0){
        right = 1;
    }else if (dx < 0){
        right = 0;
    }
}

vector<Node> DOG::findPath(int startX, int startY, int goalX, int goalY, const vector<vector<int>>& grid) {
    if (grid[goalY][goalX] == 1) {
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                int newX = goalX + dx;
                int newY = goalY + dy;

                if (newX >= 0 && newX < grid[0].size() && newY >= 0 && newY < grid.size() && grid[newY][newX] == 0) {
                    goalX = newX;
                    goalY = newY;
                    break;
                }
            }
        }
    }
    priority_queue<Node, vector<Node>, greater<Node>> openList;
    unordered_map<int, Node> openSet;
    unordered_map<int, Node> closedSet;

    auto hash = [](int x, int y) { return (x * 10000 + y); };

    auto heuristic = [](int x1, int y1, int x2, int y2) {
        return abs(x1 - x2) + abs(y1 - y2);
    };

    openList.emplace(startX, startY, 0, heuristic(startX, startY, goalX, goalY));
    openSet[hash(startX, startY)] = openList.top();

    vector<int> dx = {1, -1, 0, 0, 1, 1, -1, -1};
    vector<int> dy = {0, 0, 1, -1, 1, -1, 1, -1};

    while (!openList.empty()) {
        Node current = openList.top();
        openList.pop();
        int currentHash = hash(current.x, current.y);
        openSet.erase(currentHash);
        closedSet[currentHash] = current;

        if (current.x == goalX && current.y == goalY) {
            vector<Node> path;
            while (current.parent != nullptr) {
                path.push_back(current);
                current = *current.parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (size_t i = 0; i < dx.size(); ++i) {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];
            int newHash = hash(newX, newY);

            if (newX < 0 || newY < 0 || newX >= grid[0].size() || newY >= grid.size() || grid[newY][newX] == 1 || closedSet.count(newHash))
                continue;

            double moveCost = (i < 4) ? 1.0 : sqrt(2.0);
            double newGCost = current.gCost + moveCost;
            double newHCost = heuristic(newX, newY, goalX, goalY);
            Node neighbor(newX, newY, newGCost, newHCost, new Node(current));

            if (!openSet.count(newHash) || newGCost < openSet[newHash].gCost) {
                openList.push(neighbor);
                openSet[newHash] = neighbor;
            }
        }
    }

    return vector<Node>();
}

void updateDogPosition(Mouse &mouse, DOG &dog, const vector<vector<int>>& grid) {
    static int lastMouseX = -1;
    static int lastMouseY = -1;

    int gridMouseX = mouse.x / TILE_WIDTH ;
    int gridMouseY = mouse.y / TILE_HEIGHT ;
    int gridDogX = dog.x / TILE_WIDTH;
    int gridDogY = dog.y / TILE_HEIGHT;

    if (gridMouseX != lastMouseX || gridMouseY != lastMouseY || dog.path.empty() || dog.pathIndex >= dog.path.size()) {
        dog.path = dog.findPath(gridDogX, gridDogY, gridMouseX, gridMouseY, grid);
        dog.pathIndex = 0;

        lastMouseX = gridMouseX;
        lastMouseY = gridMouseY;
    }

    if (!dog.path.empty() && dog.pathIndex < dog.path.size()) {
        Node nextNode = dog.path[dog.pathIndex];
        double nextX = nextNode.x * TILE_WIDTH;
        double nextY = nextNode.y * TILE_HEIGHT;

        double distance = sqrt(pow(nextX - dog.x, 2) + pow(nextY - dog.y, 2));
        if (distance > dog.speed) {
            dog.dx = (nextX - dog.x) / distance;
            dog.dy = (nextY - dog.y) / distance;

            if (dog.dx > 0) {
                dog.right = 1;
            } else if (dog.dx < 0) {
                dog.right = 0;
            }

            dog.x += dog.dx * dog.speed;
            dog.y += dog.dy * dog.speed;
        } else {
            dog.x = nextX;
            dog.y = nextY;
            dog.pathIndex++;
        }
    }
}

void Busted_Out(IMAGE &Image, BOOL &b, SOUND &gameSound){
    Image.graphics.renderTexture(Image.Busted, 0, 0);
    Image.graphics.presentScene();
    if (gameSound.dog_barking != nullptr) {
        Mix_FreeChunk(gameSound.dog_barking);
        gameSound.dog_barking = nullptr;
    }
    Mix_FreeMusic(gameSound.background_music);
    gameSound.background_music = nullptr;

    Image.graphics.play(gameSound.fail);

    SDL_Delay(3000);

    b.gamePlay1 = 0;
    b.gamePlay2 = 0;
    b.menu = 1;
}

void CheckBorder (Mouse &mouse){
    if ( mouse.x < 0){
        mouse.x= 0;
    }
    if( mouse.x+32 > SCREEN_WIDTH ){
        mouse.x = SCREEN_WIDTH -32;
    }

    if (mouse.y < 0){
        mouse.y= 0;
    }
    if ( mouse.y +32 > SCREEN_HEIGHT){
        mouse.y= SCREEN_HEIGHT-32;
    }

}
//Kiem tra va cham ngoai
int Collision1(const Mouse &mouse, const WALL &wall){
    if (mouse.x + 32 > wall.x && mouse.x + 32 < wall.x + 5 && mouse.y + 32 > wall.y && mouse.y + 32 < wall.y + wall.h) return 1;
    if (mouse.x < wall.x + wall.w && mouse.x > wall.x +wall.w -5 && mouse.y + 32 > wall.y && mouse.y + 32 < wall.y + wall.h) return 2;
    if (mouse.x + 32> wall.x && mouse.x< wall.x + wall.w && mouse.y + 32 > wall.y && mouse.y +32 < wall.y + 5) return 3;
    if (mouse.x + 32> wall.x && mouse.x< wall.x + wall.w && mouse.y + 32 < wall.y + wall.h && mouse.y + 32 > wall.y + wall.h - 5) return 4;
    return 0;

}
int Collision2(const Mouse &mouse, const OBJECTS &ob){
    if (mouse.x + 32 >= ob.x && mouse.x + 32 <= ob.x + 3 && mouse.y + 32 >= ob.y && mouse.y + 32 <= ob.y + ob.h) return 1;
    if (mouse.x <= ob.x + ob.w && mouse.x >= ob.x + ob.w - 3 && mouse.y + 32 >= ob.y && mouse.y + 32 <= ob.y + ob.h) return 2;
    if (mouse.x + 32 >= ob.x && mouse.x <= ob.x + ob.w && mouse.y + 32 >= ob.y && mouse.y + 32 <= ob.y + 3) return 3;
    if (mouse.x + 32 >= ob.x && mouse.x <= ob.x + ob.w && mouse.y + 32 <= ob.y + ob.h && mouse.y + 32 >= ob.y + ob.h - 3) return 4;
    return 0;
}

//Kiem tra ben trong
int Collision3(const Mouse &mouse, const OBJECTS &ob){
    if (mouse.x <= ob.x + ob.w && mouse.x + 32 >= ob.x && mouse.y <= ob.y + ob.h -32 && mouse.y + 32 >= ob.y) return 1;
    return 0;
}

int Collision3(const Mouse &mouse, const ZONE &z){
    if (mouse.x < z.x + z.w && mouse.x + 32 > z.x && mouse.y <= z.y + z.h -32&& mouse.y + 32 >= z.y) return 1;
    return 0;
}

int Collision3(const Mouse &mouse, const DOG &dog){
    if (mouse.x <= dog.x + dog.w && mouse.x + 32 >= dog.x && mouse.y <= dog.y + dog.h && mouse.y + 32 >= dog.y) return 1;
    return 0;
}

int CollisionWithCar(const Mouse &mouse, const SDL_Rect &z){
    if (mouse.x < z.x + z.w && mouse.x + 32 > z.x && mouse.y <= z.y + z.h -32&& mouse.y + 32 >= z.y) return 1;
    return 0;
}

void CheckCollisionWall(Mouse &mouse, vector<WALL> &walls) {
    for (const auto &wall : walls) {
        if (Collision1(mouse, wall) == 1) mouse.x = wall.x - 32;
        if (Collision1(mouse, wall) == 2) mouse.x = wall.x + wall.w;
        if (Collision1(mouse, wall) == 3) mouse.y = wall.y - 32;
        if (Collision1(mouse, wall) == 4) mouse.y = wall.y + wall.h - 32;

    }
}

void CheckNameObject(OBJECTS &ob, TILEMAP &fullObjectsImage, BAG &Bag, SOUND &gameSound){
    const Uint8* Key = SDL_GetKeyboardState(NULL);
    if (ob.name == "ancient_vase"){
        InteractY0_Y_OI2(ob, Key, fullObjectsImage, Bag);

    }else if (ob.name == "phonograph"){
        InteractXY(ob, Key, fullObjectsImage, Bag);

    }else if (ob.name == "Tv" ||ob.name == "Tv2"){
        InteractY0_Y_Y1_OI2(ob, Key, fullObjectsImage, Bag);

    }else{
        if (Key[SDL_SCANCODE_E]){
            if (ob.cost != 0){
                fullObjectsImage.graphics.play(gameSound.cash_register);
                Bag.money += ob.cost;
                ob.cost = 0;
            }
        }
    }


}

void CheckCollisionObjects(Mouse &mouse, vector<OBJECTS> &objects, TILEMAP &fullObjectsImage, BAG &Bag, SOUND &gameSound){
        for (auto &ob : objects){
            if (ob.exist){
                if (Collision2(mouse, ob)== 1){
                    mouse.x = ob.x - 32;
                    CheckNameObject(ob,  fullObjectsImage, Bag, gameSound);
                }
                if (Collision2(mouse, ob)== 2){
                    mouse.x = ob.x + ob.w;
                    CheckNameObject(ob,  fullObjectsImage, Bag, gameSound);
                }
                if (Collision2(mouse, ob)== 3){
                    mouse.y = ob.y - 32;
                    CheckNameObject(ob,  fullObjectsImage, Bag, gameSound);
                }
                if (Collision2(mouse, ob)== 4){
                    mouse.y = ob.y + ob.h - 32;
                    CheckNameObject(ob,  fullObjectsImage, Bag, gameSound);
                }
            }else{
                if (Collision3(mouse, ob)== 1){
                    CheckNameObject(ob,  fullObjectsImage, Bag, gameSound);
                }

            }

        }

}

void CheckCollisionCamera(Mouse &mouse, const vector<ZONE> &camerascan, const bool &camnow, IMAGE &Image, BOOL &b, SOUND &gameSound){

    for (auto cs : camerascan){
        if (Collision3(mouse, cs)){
            if (camnow){
                if (cs.name == "CamScan1_1") Busted_Out(Image, b, gameSound);
                if (cs.name == "CamScan2_1") Busted_Out(Image, b, gameSound);
                if (cs.name == "CamScan3_1") Busted_Out(Image, b, gameSound);
                if (cs.name == "CamScan4_1") Busted_Out(Image, b, gameSound);
            }else{
                if (cs.name == "CamScan1_2") Busted_Out(Image, b, gameSound);
                if (cs.name == "CamScan2_2") Busted_Out(Image, b, gameSound);
                if (cs.name == "CamScan3_2") Busted_Out(Image, b, gameSound);
                if (cs.name == "CamScan4_2") Busted_Out(Image, b, gameSound);
            }
        }
    }
}

void CheckNameVCL(const ZONE vcl, Graphics &graphics, const TILEMAP &fullObjectsImage){
    if (vcl.name == "v1") VungCheKhuat_xy_OI1(vcl, graphics, fullObjectsImage);
    if (vcl.name == "v2") VungCheKhuat_xx1y_OI1(vcl, graphics, fullObjectsImage);
    if (vcl.name == "v3") VungCheKhuat_xyy1_OI1(vcl, graphics, fullObjectsImage);
    if (vcl.name == "v4") VungCheKhuat_xx1yy1_OI1(vcl, graphics, fullObjectsImage);
    if (vcl.name == "v4_OI2") VungCheKhuat_xx1yy1_OI2(vcl, graphics, fullObjectsImage);
    if (vcl.name == "tv") VungCheKhuat_xyy1_OI2(vcl, graphics, fullObjectsImage);

}


void CheckCollisionObjectsToRender(const Mouse &mouse, const vector<ZONE> vungchelap,  Graphics &graphics, const TILEMAP &fullObjectsImage ){
    for (auto vcl : vungchelap){
        if (Collision3(mouse, vcl)) CheckNameVCL(vcl, graphics, fullObjectsImage);
    }

}



#endif // GAME_H
