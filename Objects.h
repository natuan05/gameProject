#ifndef OBJECTS_H
#define OBJECTS_H

#include "def.h"

using namespace std;

struct WALL{

    int x;
    int y;
    int w;
    int h;

    WALL(int _x, int _y, int _w, int _h){
        x= _x;
        y= _y;
        w= _w;
        h= _h;
    }
};

struct OBJECTS{
    string name;
    bool exist = 1;
    int cost;
    int weight;

    int x;
    int y;
    int w;
    int h;

    OBJECTS (string _name, int _cost,int _weight, int _x, int _y, int _w, int _h ){
        name= _name;
        cost = _cost;
        weight= _weight;
        x= _x;
        y= _y;
        w= _w;
        h= _h;
    }

};

struct CAMERASCAN{
    string name;

    int x;
    int y;
    int w;
    int h;

    CAMERASCAN(string _name, int _x, int _y, int _w, int _h){
        name = _name;
        x= _x;
        y= _y;
        w= _w;
        h= _h;
    }
};

struct VUNGCHELAP{
    string name;
    int x;
    int y;
    int w;
    int h;
    VUNGCHELAP(string _name, int _x, int _y, int _w, int _h){
        name = _name;
        x= _x;
        y= _y;
        w= _w;
        h= _h;
    }
};


vector <WALL> WallInit(){
    vector <WALL> walls;
    walls.emplace_back(640, 416, 32, 288);
    walls.emplace_back(1216, 64, 32, 640);
    walls.emplace_back(640, 64, 608, 32);
    walls.emplace_back(640, 64, 32, 256);
    walls.emplace_back(896, 64, 32, 256);
    walls.emplace_back(896, 288, 160, 32);
    walls.emplace_back(1120, 288, 128, 32);
    walls.emplace_back(832, 416, 224, 32);
    walls.emplace_back(1120, 416, 128, 32);
    walls.emplace_back(832, 416, 32, 160);
    walls.emplace_back(832, 640, 32, 64);
    walls.emplace_back(960, 512, 32, 192);
    walls.emplace_back(832, 544, 160, 32);
    walls.emplace_back(960, 416, 32, 64);
    walls.emplace_back(288, 416, 32, 320);
    walls.emplace_back(288, 0, 32, 320);
    walls.emplace_back(640, 672, 608, 32);
    walls.emplace_back(832, 608, 32, 96);
    walls.emplace_back(832, 416, 32, 160);
    return walls;

}

vector<OBJECTS> ObjectsInit(){
    vector<OBJECTS> ob;
    ob.emplace_back("singlesofa1", 200, 3, 717, 237, 38, 19);
    ob.emplace_back("singlesofa2", 200, 3, 717, 142, 38, 18);
    ob.emplace_back("doublesofa", 0, 0, 672.25, 173, 31.75, 50.73);
    ob.emplace_back("table", 0, 0, 720, 179, 32, 34);
    ob.emplace_back("fireplace", 0, 0, 768, 96, 64, 32);
    ob.emplace_back("clock", 0, 0, 672, 96, 32, 32);
    ob.emplace_back("TableTv", 0, 0, 832, 160, 27, 64);
    return ob;
}

vector<CAMERASCAN> CamScanInit(){
    vector<CAMERASCAN> CS;
    CS.emplace_back("CamScan4_1", 768, 288, 128, 128);
    CS.emplace_back("CamScan4_2", 768, 192, 128, 128);
    CS.emplace_back("CamScan3_2", 672, 544, 128, 128);
    CS.emplace_back("CamScan3_1", 672, 448, 128, 128);
    CS.emplace_back("CamScan2_2", 512, 288, 128, 128);
    CS.emplace_back("CamScan2_1", 512, 192, 128, 128);
    CS.emplace_back("CamScan1_1", 160, 416, 128, 128);
    CS.emplace_back("CamScan1_2", 160, 320, 128, 128);

    return CS;

}

vector<VUNGCHELAP> VCLInit(){
    vector<VUNGCHELAP> vcl;
    vcl.emplace_back("doublesofa", 672, 160, 32, 14);
    vcl.emplace_back("table", 720, 171, 32, 9);
    vcl.emplace_back("singlesofa2", 717, 129, 38, 14);
    vcl.emplace_back("singlesofa1", 717, 227, 38, 11);

    return vcl;
}

#endif

