#pragma once

#include <vector>
#include <cstdlib>
#include <glm/glm.hpp>

#include "Enum.h"

enum STATE {
    // Player
    ALIVE,
    // AI
    SEARCH,
    FOUND,
    ATTACK,
    ESCAPE,
    // both
    DEAD
};
enum CHAR_TYPE {
    PLAYER,
    ENEMY
};

class Character
{
public:
    Character(int _x, int _y, int _maxHP, int _STR, int _VIT, STATE _state, DIRECTION _dir, CHAR_TYPE _type);

    void move(DIRECTION _dir);
    void moveTo(glm::vec2 _pos);
    void back();
    void attack(class Character& _enemy);
    void receiveDamage(int _damage);

    void setPos(int _x, int _y);
    void setPos(glm::vec2 _pos);
    void setState(STATE _state);
    void setDir(DIRECTION _dir);

    glm::vec2 getPos() {return mPos;}
    int getX() {return mPos.x;}
    int getY() {return mPos.y;}
    STATE getState() {return mState;}
    DIRECTION getDir() {return mDir;}
    CHAR_TYPE getType() {return mType;}

protected:
    STATE mState;
    DIRECTION mDir;
    CHAR_TYPE mType;
    glm::vec2 mPos;
    int maxHP, STR, VIT;
    int nowHP;
};

Character::Character(int _x, int _y, int _maxHP, int _STR, int _VIT, STATE _state, DIRECTION _dir, CHAR_TYPE _type)
:mPos(glm::vec2(_x, _y)), maxHP(_maxHP), nowHP(_maxHP), STR(_STR), VIT(_VIT), mState(_state), mDir(_dir), mType(_type)
{
}

void Character::move(DIRECTION _dir) {
    switch (_dir) {
        case LEFT:  mPos.x--; break;
        case RIGHT: mPos.x++; break;
        case UP:    mPos.y--; break;
        case DOWN:  mPos.y++; break;
    }
    mDir = _dir;
}

void Character::moveTo(glm::vec2 _pos) {
    if(_pos.x > mPos.x) move(RIGHT);
    else if(_pos.x < mPos.x) move(LEFT);
    else if(_pos.y > mPos.y) move(DOWN);
    else move(UP);
}

void Character::back() {
    switch (mDir) {
        case LEFT:  mPos.x++; break;
        case RIGHT: mPos.x--; break;
        case UP:    mPos.y++; break;
        case DOWN:  mPos.y--; break;
    }
}

void Character::attack(Character& _opponent) {
    _opponent.receiveDamage(STR);
}

void Character::receiveDamage(int _damage) {
    nowHP -= abs(_damage - VIT);
    if(nowHP <= 0) {
        mState = DEAD;
    }
}

void Character::setPos(int _x, int _y) {
    mPos.x = _x;
    mPos.y = _y;
}

void Character::setPos(glm::vec2 _pos) {
    mPos.x = _pos.x;
    mPos.y = _pos.y;
}

void Character::setState(STATE _state) {
    mState = _state;
}


void Character::setDir(DIRECTION _dir) {
    mDir = _dir;
}

