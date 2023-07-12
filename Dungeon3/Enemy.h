#pragma once

#include "Actor.h"
#include "AIState/Patrol.h"

class Enemy : public Actor
{
public:
    Enemy(class Dungeon* dungeon);
    void UpdateActor() override;

private:
    bool CanMoveTo(const Vector2& pos) override;
};