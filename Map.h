#ifndef MAP_H
#define MAP_H


#include "def.h"
#include "graphics.h"
#include "game.h"

using namespace std;

// Hàm để tải tile map từ tệp CSV
vector<vector<int>> loadTileMapFromCSV(const string& filePath) {
    vector<vector<int>> tileMap(MAP_HEIGHT, vector<int>(MAP_WIDTH, 0));

    ifstream file(filePath);
    if (file.is_open()) {
        string line;
        int row = 0;
        while (getline(file, line) && row < MAP_HEIGHT) {
            stringstream iss(line);
            string value;
            int col = 0;
            while (getline(iss, value, ',') && col < MAP_WIDTH) {
                tileMap[row][col] = stoi(value);
                col++;
            }
            row++;
        }
        file.close();
        return tileMap;
    } else {
        cerr << "Khong the mo file: " << filePath << endl;
    }
}





#endif
