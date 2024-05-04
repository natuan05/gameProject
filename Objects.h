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
    WALL(){
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

    OBJECTS (){
    }

};

struct ZONE{
    string name;

    int x;
    int y;
    int w;
    int h;

    ZONE(string _name, int _x, int _y, int _w, int _h){
        name = _name;
        x= _x;
        y= _y;
        w= _w;
        h= _h;
    }

    ZONE(){
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
    ob.emplace_back("washstand1", 0, 0, 931, 448, 26.75, 15.25);
    ob.emplace_back("washstand2", 0, 0, 899, 576, 26.75, 15.25);
    ob.emplace_back("bathtub1", 0, 0, 864, 512, 64, 32);
    ob.emplace_back("bathtub2", 0, 0, 896, 640, 64, 32);
    ob.emplace_back("Table2", 0, 0, 864, 96, 32, 32);
    ob.emplace_back("pots1", 0, 0, 675, 304, 26, 12);
    ob.emplace_back("pots2", 0, 0, 867, 304, 26, 12);
    ob.emplace_back("kennel", 0, 0, 322, 465, 28, 15);
    ob.emplace_back("truck", 0, 0, 160, 32, 64, 128);
    ob.emplace_back("Bep", 0, 0, 672, 640, 159, 32);
    ob.emplace_back("BanAn", 0, 0, 704, 538.73, 96, 47.63);
    ob.emplace_back("TableTv2", 0, 0, 1058.75, 512, 27.75, 64);
    ob.emplace_back("bed", 0, 0, 1152, 517, 64, 59);
    ob.emplace_back("bookshelf", 0, 0, 992, 640, 224, 32);
    ob.emplace_back("Ke", 0, 0, 1194.96, 486.45, 20.77, 25.51);

    return ob;
}

vector<ZONE> CamScanInit(){
    vector<ZONE> CS;
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

vector<ZONE> VCLInit(){
    vector<ZONE> vcl;
    vcl.emplace_back("v1", 672, 160, 32, 14);
    vcl.emplace_back("v2", 720, 171, 32, 9);
    vcl.emplace_back("v2", 717, 129, 38, 14);
    vcl.emplace_back("v2", 717, 227, 38, 11);
    vcl.emplace_back("v2", 704, 527.275, 32, 14.8922818181819);
    vcl.emplace_back("v1", 842.875, 143.75, 9.25, 43.375);
    vcl.emplace_back("v1", 1195, 480, 20.9375, 8);
    vcl.emplace_back("v3", 672.75, 261.75, 30.875, 44.4545454545454);
    vcl.emplace_back("v3", 864.563, 262.167, 30.875, 44.8181818181818);
    vcl.emplace_back("v4", 672.182, 623.818, 64.1818, 18.6477);
    vcl.emplace_back("v4", 736.364, 623.818, 63.4545, 18.7273);
    vcl.emplace_back("v4", 792.545, 623.818, 39.6364, 18.9773);
    vcl.emplace_back("v2", 736, 527.534, 64, 14.4431818181819);
    vcl.emplace_back("v1", 320, 448, 32.125, 18.9375);
    vcl.emplace_back("v4", 992, 628, 64, 16);
    vcl.emplace_back("v4", 1056, 628, 64, 16);
    vcl.emplace_back("v4", 1120, 628, 64, 16);
    vcl.emplace_back("v3", 1184, 628, 31.9565217391305, 16);

    return vcl;
}



#endif

