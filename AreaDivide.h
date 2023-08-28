#pragma once

#include <iostream>
#include <random>

#include "common.h"

using namespace std;

int areaCount = 0;

void divide(int areaID)
{
    if(areaCount > AREA_MAX) {
        return;
    }

    int newAreaID = areaCount;
// エリア分割が失敗したと用に値を退避
    int w = areas[areaID].w;
    int h = areas[areaID].h;
// エリアの長辺で分割
    if(areas[areaID].w > areas[areaID].h) {
        areas[areaID].w /= 2;
        areas[newAreaID] = Area(
            areas[areaID].x + areas[areaID].w, 
            areas[areaID].y, 
            w - areas[areaID].w, 
            areas[areaID].h
        );
    } else {
        areas[areaID].h /= 2;
        areas[newAreaID] = Area(
            areas[areaID].x, 
            areas[areaID].y + areas[areaID].h, 
            areas[areaID].w, 
            h - areas[areaID].h
        );
    }
// エリアの最小サイズに満たない場合はキャンセル
    if(areas[areaID].w < AREA_SIZE_MIN || areas[areaID].h < AREA_SIZE_MIN
        || areas[newAreaID].w < AREA_SIZE_MIN || areas[newAreaID].h < AREA_SIZE_MIN) {
            areas[areaID].w = w;
            areas[areaID].h = h;
            return;
    }

    areaCount++;
    devidArea(randomNumber % areaCount);
}

void generate()
{

}