#include "Player.h"
#include "Dungeon.h"

Player::Player(Dungeon *dungeon)
    : Actor(dungeon)
{
}

void Player::UpdateActor()
{
    Actor::UpdateActor();
    Vector2 pos = GetPosition();

    SetPosition(pos);
}

void Player::ProcessKeyboard(const char input)
{
    Vector2 before = GetPosition();
    Vector2 after = GetPosition();
    switch (input)
    {
    case 'w':
        after.y-=1;
        break;
    case 'a':
        after.x-=1;
        break;
    case 's':
        after.y+=1;
        break;
    case 'd':
        after.x+=1;
        break;
    }
    if (CanMoveTo(after))
    {
        Vector2 before = GetPosition();
        GetDungeon()->changedMap[(int)before.y][(int)before.x] = GetDungeon()->originalMap[(int)before.y][(int)before.x];
        SetPosition(after);
        GetDungeon()->changedMap[(int)after.y][(int)after.x] = PLAYER;
    }
}

bool Player::CanMoveTo(const Vector2& pos)
{
    if(GetDungeon()->changedMap[(int)pos.y][(int)pos.x] != FLOOR 
    && GetDungeon()->changedMap[(int)pos.y][(int)pos.x] != AISLE) return false;
    if(GetDungeon()->changedMap[(int)pos.y][(int)pos.x] == ENEMY) return false;
    return true;
}