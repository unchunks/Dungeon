#include "Enemy.h"
#include "Dungeon.h"

Enemy::Enemy(Dungeon *dungeon)
    : Actor(dungeon)
{
}

void Enemy::UpdateActor()
{
    Actor::UpdateActor();
    Vector2 pos = GetPosition();

    SetPosition(pos);
}

bool Enemy::CanMoveTo(const Vector2& pos)
{
    if(GetDungeon()->changedMap[(int)pos.y][(int)pos.x] != FLOOR 
    && GetDungeon()->changedMap[(int)pos.y][(int)pos.x] != AISLE) return false;
    if(GetDungeon()->changedMap[(int)pos.y][(int)pos.x] == ENEMY) return false;
    return true;
}