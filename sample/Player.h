#pragma once

#include "Actor.h"

class Player : public Actor
{
public:
    Player(class Dungeon* dungeon);
    void UpdateActor() override;//float deltaTime
    void ProcessKeyboard(const char state);//u_int8_t*
private:
};