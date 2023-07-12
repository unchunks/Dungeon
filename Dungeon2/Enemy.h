#pragma once

#include "Character.h"

class Enemy : public Character {
public:
    Enemy();

private:
    bool canMove(int _x, int _y);
};

Enemy::Enemy() : Character("E ", 100, 10, 10) {
}

bool Enemy::canMove(int _x, int _y) {
    // if(player.getX() == _x && player.getY() == _y) return false;
    // if((mapBuff[_y][_x] != FLOOR) && (mapBuff[_y][_x] != AISLE)) return false;
    return true;
}
