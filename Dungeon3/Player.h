#pragma once

#include "Actor.h"

class Player : public Actor
{
public:
    Player(class Dungeon* dungeon);
    void UpdateActor() override;
    void ProcessKeyboard(const char state);

private:
    bool CanMoveTo(const Vector2& pos) override;
};