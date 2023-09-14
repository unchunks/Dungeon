#pragma once

#include <deque>

#include "AStar.h"
#include "Character.h"

class Enemy : public Character
{
public:
    Enemy(int _x, int _y, int _maxHP, int _STR, int _VIT);
    void walk();
    void setGoal(CELL_TYPE dungeon[BUFF_FLOOR_H][BUFF_FLOOR_W], glm::vec2 _goal);

    int getRouteSize() {return route.size();}

private:
    std::deque<glm::vec2> route;
    glm::vec2 goal;
    glm::vec2 nextPos;
    int elapsedTurn;

};

Enemy::Enemy(int _x, int _y, int _maxHP, int _STR, int _VIT)
: Character(_x, _y, _maxHP, _STR, _VIT, SEARCH, DOWN, ENEMY), elapsedTurn(15)
{
}

void Enemy::walk()
{
    nextPos = route[0];
    // route.pop_front();
    // moveTo(nextPos);
}

void Enemy::setGoal(CELL_TYPE dungeon[BUFF_FLOOR_H][BUFF_FLOOR_W], glm::vec2 _goal)
{
    goal = _goal;
    std::cout << "GOAL ==> (" << goal.x << ", " << goal.y << ")\n";
    route = Astar(dungeon, 0, mPos.x, mPos.y, goal.x, goal.y);
    for(auto pos: route)
    {
        std::cout << "(" << pos.x << ", " << pos.y << ")\n";
    }
}
