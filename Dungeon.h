#pragma once

#include <iostream>
#include <random>
#include <glm/glm.hpp>

#include "AreaDivide.h"

#include "Actor.h"
#include "Player.h"
#include "Enemy.h"

#include "Character.h"

const int NUM_ENEMY = 1;
const int ENEMY_SEARCH_RANGE = 10;

class Dungeon
{
public:
    void init();
    void run();
    void quit();

private:
    char input = 'a';
    bool isRunning = true;
    AreaDivide areaDivide;

    Player player = Player(0, 0, 0, 0, 0);
    std::vector<Enemy> enemies = std::vector<Enemy>(NUM_ENEMY, Enemy(0, 0, 0, 0, 0));
    std::vector<Actor> actors = std::vector<Actor>();

// プレイヤーと敵についての関数
    int isOtherPos(int x, int y);
    bool canGetOn(int x, int y);

// プレイヤーについての関数
    bool isPlayerPos(int x, int y);
    void arrangementPlayer(int roomCount);

// 敵についての関数
};

void Dungeon::init()
{
    actors.push_back(player);
    actors.insert(actors.end(), enemies.begin(), enemies.end());

    areaDivide.initFloor();
    areaDivide.generate();
    areaDivide.fillSurround();
    areaDivide.randomEraseDeadEnd();
    areaDivide.identificationWallKind();
}

void Dungeon::run()
{
    while(isRunning)
    {
        areaDivide.output();
        std::cin >> input;
        if(input == 'q') isRunning = false;
    }
}

void Dungeon::quit()
{
}


int Dungeon::isOtherPos(int x, int y)
{
    int sameNum = 0;
    for(Actor a : actors)
    {
        if((a.getX() == x) && (a.getY() == y))
            sameNum++;
    }
    return sameNum;
}

bool Dungeon::canGetOn(int x, int y) 
{
    if((areaDivide.buff[y][x] != FLOOR) && (areaDivide.buff[y][x] != AISLE)) 
        return false;
    if(isOtherPos(x, y) > 1) 
        return false; 
    // if(isPlayerPos(x, y)) return false;
    // int same = 0;
    // for(Actor a : actors) {
    //     if(isEnemyPos(e, x, y)) same++;
    // }
    // if(same > 1) return false;
    return true;
}




bool Dungeon::isPlayerPos(int x, int y) {
    if((x == player.getX()) && (y == player.getY())) return true;
    return false;
}

void Dungeon::arrangementPlayer(int roomCount) {
    int roomNum = rand() % roomCount;
    Area area = areaDivide.getArea(roomNum);
    int px = area.room.x + rand()%area.room.w;
    int py = area.room.y + rand()%area.room.h;

    while(!canGetOn(px, py)) {
        px = area.room.x + rand()%area.room.w;
        py = area.room.y + rand()%area.room.h;
    }

    player.setPos(px, py);
}
