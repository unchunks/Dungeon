#pragma once

#include "Actor.h"

class Enemy : public Actor {
public:
    Enemy(int _x, int _y, int _maxHP, int _STR, int _VIT);
    void randomMove();
    void setState(STATE state);

    std::vector<vec2> toPlayer;
    int elapsedTurn;

private:

};

Enemy::Enemy(int _x, int _y, int _maxHP, int _STR, int _VIT)
: Actor(_x, _y, _maxHP, _STR, _VIT, SEARCH, DOWN), elapsedTurn(15)
{
}

void Enemy::randomMove() {
    switch (rand() % 4)
    {
        case 0: move(LEFT); break;
        case 1: move(RIGHT);break;
        case 2: move(UP);   break;
        case 3: move(DOWN); break;
    }
}

void Enemy::setState(STATE state) {
    mState = state;
}
