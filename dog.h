#ifndef _DOG_H
#define _DOG_H

#include "def.h"

struct DOG{
    int x = 320;
    int y = 500;
    int w = 48;
    int h = 24;
    double dx = 0, dy = 0;
    double speed = INITIAL_DOGSPEED;
    double speed2 = (double)speed/(sqrt(2));

};

void updateDogPosition(Mouse &mouse, DOG &dog) {
    // Tính toán khoảng cách giữa chó và chuột
    float distance = sqrt(pow(mouse.x - dog.x, 2) + pow(mouse.y - dog.y, 2));

    // Nếu khoảng cách lớn hơn ngưỡng, chó sẽ di chuyển theo hướng của chuột
    if (distance > 0) {
        // Tính toán vector hướng
        float direction_x = (mouse.x - dog.x) / distance;
        float direction_y = (mouse.y - dog.y) / distance;

        // Di chuyển chó theo hướng của chuột với tốc độ chó
        dog.x += direction_x * dog.speed;
        dog.y += direction_y * dog.speed;
    }
}


#endif // _DOG_H
