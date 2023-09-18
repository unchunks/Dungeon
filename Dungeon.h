#pragma once

#include <iostream>
#include <random>
#include <glm/glm.hpp>

#include "AreaDivide.h"

#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Const.h"

class Dungeon
{
public:
    void init();
    void run();
    void quit();

    void update();

private:
    char input = 'a';
    bool isRunning = true;
    AreaDivide areaDivide;

    Player player = Player(0, 0, 0, 0, 0);
    std::vector<Enemy> enemies = std::vector<Enemy>(NUM_ENEMY, Enemy(0, 0, 0, 0, 0));

    int isOtherPos(int x, int y);
    bool canGetOn(int x, int y);
    glm::vec2 getRandomPos(int roomCount);
};

void Dungeon::init()
{
    areaDivide.initFloor();
    areaDivide.generate();
    areaDivide.fillSurround();
    areaDivide.randomEraseDeadEnd();
    areaDivide.identificationWallKind();

    glm::vec2 pos = getRandomPos(areaDivide.getRoomNum());
    player.setPos(pos);
    for(auto& e : enemies)
    {
        pos = getRandomPos(areaDivide.getRoomNum());
        e.setPos(pos);
    }
    for(auto e : enemies)
    {
        std::cout << "(" << e.getX() << ", " << e.getY() << ")\n";
    }
}

void Dungeon::run()
{
    while(isRunning)
    {
        areaDivide.output(player, enemies);
        std::cin >> input;
        if(input == 'q') isRunning = false;
        update();
    }
}

void Dungeon::quit()
{
}

void Dungeon::update()
{
    switch(input)
    {
        case 'w':
            player.move(DIRECTION::UP);
            break;
        case 'a':
            player.move(DIRECTION::LEFT);
            break;
        case 's':
            player.move(DIRECTION::DOWN);
            break;
        case 'd':
            player.move(DIRECTION::RIGHT);
            break;
    }
    if(!canGetOn(player.getX(), player.getY()))
        player.back();
    
    for(auto& e : enemies)
    {
        std::cout << "残り距離　: " << e.getRouteSize() << std::endl;
        std::cout << "経過ターン: " << e.getElapsedTurn() << std::endl;
        switch(e.getState())
        {
        case SEARCH:
            if(abs(e.getX() - player.getX()) + abs(e.getY() - player.getY()) <= ENEMY_FIND_RANGE)
                e.setState(FOUND);
            if((e.getRouteSize() < 1) || (e.getElapsedTurn() > ENEMY_SEARCH_INTERVAL))
                e.setGoal(areaDivide.getFloor(), getRandomPos(areaDivide.areaCount));

        case FOUND:
            if(abs(e.getX() - player.getX()) + abs(e.getY() - player.getY()) > ENEMY_FIND_RANGE)
                e.setState(SEARCH);
            if((e.getRouteSize() < 1) || (e.getElapsedTurn() > ENEMY_SEARCH_INTERVAL))
                e.setGoal(areaDivide.getFloor(), player.getPos());
        }
        e.walk();
            if(!canGetOn(player.getX(), player.getY()))
                e.back();
    }
}


int Dungeon::isOtherPos(int x, int y)
{
    int sameNum = 0;
    if((player.getX() == x) && (player.getY() == y))
            sameNum++;
    for(auto a : enemies)
    {
        if((a.getX() == x) && (a.getY() == y))
            sameNum++;
    }
    return sameNum;
}

bool Dungeon::canGetOn(int x, int y) 
{
    if((areaDivide.buff[y+1][x+1] != FLOOR) && (areaDivide.buff[y+1][x+1] != AISLE)) 
        return false;
    if(isOtherPos(x, y)  > 1)
        return false;
    return true;
}

glm::vec2 Dungeon::getRandomPos(int roomCount)
{
    int roomNum = rand() % roomCount;
    Room room = areaDivide.getRoom(roomNum);
    glm::vec2 pos;
    pos.x = room.x + rand()%room.w;
    pos.y = room.y + rand()%room.h;
    while(!canGetOn(pos.x, pos.y)) {
        pos.x = room.x + rand()%room.w;
        pos.y = room.y + rand()%room.h;
    }
    return pos;
}