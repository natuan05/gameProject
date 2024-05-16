#ifndef MAP_H
#define MAP_H


#include "def.h"
#include "game.h"

using namespace std;

vector<vector<int>> LoadTileMapFromCSV(const string& filePath) {
    vector<vector<int>> tileMap(MAP_HEIGHT, vector<int>(MAP_WIDTH, 0));

    ifstream file(filePath);
    if (file.is_open()) {
        string line;
        int row = 0;
        while (getline(file, line) && row < MAP_HEIGHT) {
            stringstream ss(line);
            string value;
            int col = 0;
            while (getline(ss, value, ',') && col < MAP_WIDTH) {
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
