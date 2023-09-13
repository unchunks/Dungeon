#pragma once

#include <iostream>
#include <random>
#include <glm/glm.hpp>

#include "AreaDivide.h"

#include "Character.h"
#include "Player.h"
#include "Enemy.h"

const int NUM_ENEMY = 1;
const int ENEMY_SEARCH_RANGE = 10;

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
    areaDivide.initFloor();
    areaDivide.generate();
    areaDivide.fillSurround();
    areaDivide.randomEraseDeadEnd();
    areaDivide.identificationWallKind();

    arrangementPlayer(areaDivide.getRoomNum());
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
    std::cout << "1\n";
    if((areaDivide.buff[y+1][x+1] != FLOOR) && (areaDivide.buff[y+1][x+1] != AISLE)) 
        return false;
    std::cout << "2\n";
    if(isOtherPos(x, y)  > 1)
        return false;
    std::cout << "3\n";
    // int same = 0;
    // for(Character a : actors) {
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
    Room room = areaDivide.getRoom(roomNum);
    int px = room.x + rand()%room.w;
    int py = room.y + rand()%room.h;

    while(!canGetOn(px, py)) {
        px = room.x + rand()%room.w;
        py = room.y + rand()%room.h;
    }

    player.setPos(px, py);
}
