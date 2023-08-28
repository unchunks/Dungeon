#pragma once

#include "Room.h"

const int ROOM_MARGIN = 2;

class Area 
{
public:
    Area(int _x, int _y, int _w, int _h)
        :x(_x), y(_y), w(_w), h(_h), 
        room(x + ROOM_MARGIN, y + ROOM_MARGIN, w - ROOM_MARGIN*2, h - ROOM_MARGIN*2){};
    int x, y, w, h;
    Room room;

    Area operator = (Area area)
    {
        return Area(area.x, area.y, area.w, area.h);
    }
};
