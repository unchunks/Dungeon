#pragma once

#include "Character.h"

class Player : public Character {
public:
    Player();

    void Update(float deltaTime) override;
    void Draw() override;

private:
    bool canMove(int _x, int _y);
};

Player::Player() : Character("@ ", 100, 10, 10) {
}

bool Player::canMove(int _x, int _y) {
    // for(Enemy e : enemies) {
    //     if(e.getX() == _x && e.getY() == _y) return false;
    // }
    // if((mapBuff[_y][_x] != FLOOR) && (mapBuff[_y][_x] != AISLE)) return false;
    return true;
}
