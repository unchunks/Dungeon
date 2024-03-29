// オリジナル

#include "DMethod.h"

void Original() {
    for(int i = 0; i < AREA_MAX; i++) {
        int ax = rand() % FLOOR_W;
        int ay = rand() % FLOOR_H;
        int aw = rand() % AREA_SIZE_MIN + AREA_SIZE_MIN;
        int ah = rand() % AREA_SIZE_MIN + AREA_SIZE_MIN;
        areas[i] = Area(ax, ay, aw, ah);
        if(areas[i].room.x + areas[i].room.w >= FLOOR_W) {
            areas[i].room.x = FLOOR_W - areas[i].room.w - 1;
        }
        if(areas[i].room.y + areas[i].room.h >= FLOOR_H) {
            areas[i].room.y = FLOOR_H - areas[i].room.h - 1;
        }

        for(int y = areas[i].room.y; y < areas[i].room.y + areas[i].room.h; y++) {
            for(int x = areas[i].room.x; x < areas[i].room.x + areas[i].room.w; x++) {
                floorTYPE[y][x] = FLOOR;
            }
        }

        if(i == 0) continue;
        int aisle_x1 = areas[i - 1].room.x + (rand() % areas[i - 1].room.w);
        int aisle_y1 = areas[i - 1].room.y + (rand() % areas[i - 1].room.h);
        int aisle_x2 = areas[i].room.x + (rand() % areas[i].room.w);
        int aisle_y2 = areas[i].room.y + (rand() % areas[i].room.h);
        int mx = (aisle_x1 + aisle_x2) / 2;

        int dx = 1;
        if(aisle_x1 > aisle_x2) dx = -1;
        for(int x = aisle_x1; x != mx; x+=dx) {
            floorTYPE[aisle_y1][x] = AISLE;
        }
        for(int x = mx; x != aisle_x2; x+=dx) {
            floorTYPE[aisle_y2][x] = AISLE;
        }
        if(aisle_y1 > aisle_y2) {
            int work = aisle_y1;
            aisle_y1 = aisle_y2;
            aisle_y2 = work;
        }
        for(int y = aisle_y1; y <= aisle_y2; y++) {
            floorTYPE[y][mx] = AISLE;
        }
    }
}
