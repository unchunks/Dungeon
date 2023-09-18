#pragma once

#include <deque>

#include "AStar.h"
#include "Character.h"

class Enemy : public Character
{
public:
    Enemy(int _x, int _y, int _maxHP, int _STR, int _VIT);
    void walk();
    void setGoal(CELL_TYPE dungeon[FLOOR_H][FLOOR_W], glm::vec2 _goal);

    int getRouteSize() {return route.size();}
    int getElapsedTurn() {return elapsedTurn;}

private:
    std::deque<glm::vec2> route;
    glm::vec2 goal;
    glm::vec2 nextPos;
    int elapsedTurn;

};

Enemy::Enemy(int _x, int _y, int _maxHP, int _STR, int _VIT)
: Character(_x, _y, _maxHP, _STR, _VIT, SEARCH, DOWN, ENEMY), elapsedTurn(0)
{
}

void Enemy::walk()
{
    nextPos = route[0];
    route.pop_front();
    moveTo(nextPos);
    elapsedTurn++;
}

void Enemy::setGoal(CELL_TYPE dungeon[FLOOR_H][FLOOR_W], glm::vec2 _goal)
{
    goal = _goal;
    std::cout << "GOAL ==> (" << goal.x << ", " << goal.y << ")\n";
    route.clear();
    route = AStar(dungeon, mPos, goal);
    route.pop_front();
    elapsedTurn = 0;
}
