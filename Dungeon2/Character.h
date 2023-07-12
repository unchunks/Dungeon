#pragma once

#include <string>

#include "enum.h"

class Character {
public:
    enum DIRECTION {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    Character(std::string _icon, int _hp, int _str, int _vit);
    

    virtual void Update(float deltaTime);
    virtual void Draw();

    void put(const int _x, const int _y);
    void move(const DIRECTION direction);
    void move(const int _x, const int _y);

    std::string getIcon() { return icon; }
    int getX() { return x; }
    int getY() { return y; }

protected:
    std::string icon;

    int x, y;
    int max_HP;
    int now_HP;
    int str, vit;

    DIRECTION dir;

    virtual bool canMove(const int _x, const int _y) = 0;
};


Character::Character(std::string _icon, int _hp, int _str, int _vit) {
    icon = _icon;
    x = y = 0;
    max_HP = now_HP = _hp;
    str = _str;
    vit = _vit;
    dir = DOWN;
}

void Character::put(const int _x, const int _y) {
    x = _x;
    y = _y;
}

void Character::move(const DIRECTION direction) {
    int buffX = x;
    int buffY = y;
    switch(direction) {
        case UP:    buffY--; break;
        case DOWN:  buffY++; break;
        case LEFT:  buffX--; break;
        case RIGHT: buffX++; break;
    }
    if(!canMove(buffX, buffY)) return;
    changedMap[y][x] = originalMap[y][x];
    x = buffX;
    y = buffY;
    changedMap[y][x] = CHARACTER;
}
void Character::move(const int _x, const int _y) {
    if(_x < x)      move(LEFT);
    else if(_x > x) move(RIGHT);
    else if(_y < y) move(UP);
    else if(_y > y) move(DOWN);
}
