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
    return walls;

}

vector<OBJECTS> ObjectsInit(){
    vector<OBJECTS> ob;
    ob.emplace_back("singlesofa1", 20, 3, 717, 237, 38, 19);
    ob.emplace_back("singlesofa2", 25, 3, 717, 142, 38, 18);
    ob.emplace_back("doublesofa", 50, 0, 672.25, 173, 31.75, 50.73);
    ob.emplace_back("table", 10, 0, 720, 179, 32, 34);
    ob.emplace_back("fireplace", 5, 0, 768, 96, 64, 32);
    ob.emplace_back("clock", 20, 0, 672, 96, 32, 32);
    ob.emplace_back("TableTv", 0, 0, 832, 160, 27, 64);
    ob.emplace_back("Tv", 0, 0, 832, 160, 27, 64);
    ob.emplace_back("washstand1", 5, 0, 931, 448, 26.75, 15.25);
    ob.emplace_back("washstand2", 0, 0, 899, 576, 26.75, 15.25);
    ob.emplace_back("bathtub1", 10, 0, 864, 512, 64, 32);
    ob.emplace_back("bathtub2", 50, 0, 896, 640, 64, 32);
    ob.emplace_back("Table2", 5, 0, 864, 96, 32, 32);
    ob.emplace_back("pots1", 10, 0, 675, 300, 26, 18);
    ob.emplace_back("pots2", 50, 0, 867, 300, 26, 18);
    ob.emplace_back("kennel", 30, 0, 322, 465, 28, 15);
    ob.emplace_back("truck", 0, 0, 160, 32, 64, 128);
    ob.emplace_back("Bep", 70, 0, 672, 640, 159, 32);
    ob.emplace_back("BanAn", 30, 0, 704, 538.73, 96, 47.63);
    ob.emplace_back("TableTv2", 50, 0, 1058.75, 512, 27.75, 64);
    ob.emplace_back("Tv2", 50, 0, 1058.75, 512, 27.75, 64);
    ob.emplace_back("bed", 50, 0, 1152, 510, 64, 65);
    ob.emplace_back("bookshelfmini", 100, 0, 1120, 640, 96, 32);
    ob.emplace_back("Ke", 100, 0, 1195, 486, 21, 27);
    ob.emplace_back("wardrobe", 150, 0, 992, 544, 17, 128);
    ob.emplace_back("bookshelf1", 20, 0, 928, 220, 128, 22);
    ob.emplace_back("bookshelf2", 50, 0, 1088, 220, 128, 22);
    ob.emplace_back("bookshelf3", 0, 0, 928, 157, 128, 21);
    ob.emplace_back("bookshelf4", 0, 0, 1088, 157, 128, 20);
    ob.emplace_back("phonograph", 200, 0, 672, 147, 32, 14);
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
    vcl.emplace_back("v2", 704, 527, 32, 15);
    vcl.emplace_back("v1", 1195, 480, 21, 8);
    vcl.emplace_back("v3", 673, 256, 31, 44);
    vcl.emplace_back("v3", 865, 256, 31, 45);
    vcl.emplace_back("v4", 672, 624, 64, 19);
    vcl.emplace_back("v4", 736, 624, 63, 19);
    vcl.emplace_back("v4", 792, 624, 40, 19);
    vcl.emplace_back("v2", 736, 528, 64, 14);
    vcl.emplace_back("v1", 320, 448, 32, 19);
    vcl.emplace_back("v4", 1120, 628, 64, 16);
    vcl.emplace_back("v3", 1184, 628, 32, 16);
    vcl.emplace_back("v4_OI2", 928, 112, 64, 48);
    vcl.emplace_back("v4_OI2", 1088, 112, 64, 48);
    vcl.emplace_back("v4", 1088, 176, 64, 48);
    vcl.emplace_back("v3", 992, 495, 19, 50);
    vcl.emplace_back("v4_OI2", 992, 112, 64, 48);
    vcl.emplace_back("v4_OI2", 1152, 112, 64, 48);
    vcl.emplace_back("v4", 1152, 176, 64, 48);
    vcl.emplace_back("v4", 993, 176, 64, 48);
    vcl.emplace_back("v4", 929, 176, 64, 48);
    vcl.emplace_back("v1", 672, 134, 32, 16);

    return vcl;
}



#endif

