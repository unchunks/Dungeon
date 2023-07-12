#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

#include "gen.h"

#include "Character.h"
#include "Player.h"
#include "Enemy.h"

const int ENEMY_NUMBER = 5;

class DungeonManage {
public:
    DungeonManage();

    void generate();
    void initChar();
    void initItem();

    void input();
    void update();
    void output();

    void quit();

    bool getIsRunning() { return isRunning; }

private:
    char inputValue;
    bool isRunning;
    std::string map[mapH][mapW];

    std::vector<Character> characters = std::vector<Character>(ENEMY_NUMBER + 1);

    void mapConversion(CELL_TYPE originalMap[mapH][mapW]);
    bool isPlayerPos(int x, int y);
    bool isEnemiesPos(int x, int y);
    std::string posToEnemyIcon(int x, int y);
};

DungeonManage::DungeonManage() {
    inputValue = ' ';
    isRunning = true;

    for(int y = 0; y < mapH; y++) {
        for(int x = 0; x < mapW; x++) {
            map[y][x] = "■ ";
        }
    }
}
void DungeonManage::generate() {
    std::cout << "ダンジョン生成方法を選択してください\n";
    std::cout << "１：区域分割法\n";
    std::cout << "２：オリジナル\n";
    std::cin >> inputValue;
    // CELL_TYPE originalMap[mapH][mapW];
    for(int y = 0; y < mapH; y++) {
        for(int x = 0; x < mapW; x++) {
            originalMap[y][x] = WALL_ALL;
        }
    }
    switch(inputValue) {
        case '1':
            gen1(originalMap);
            break;
        case '2':
            gen2(originalMap);
            break;
        default:
            std::cout << "不適切な値が入力されました。プログラムを終了します。\n";
    }

// 外周を壁で埋める
    for(int y = 0; y < mapH; y++) {
        originalMap[y][0] = originalMap[y][mapW-1] = WALL_ALL;
    }
    for(int x = 0; x < mapW; x++) {
        originalMap[0][x] = originalMap[mapH-1][x] = WALL_ALL;
    }

// 行き止まりをランダムでなくす
    for(int y = 0; y < mapH; y++) {
        for(int x = 0; x < mapW; x++) {
            if(originalMap[y][x] == WALL_ALL) continue;
            int n = 0;
            if(originalMap[y+1][x] == WALL_ALL) n++;
            if(originalMap[y-1][x] == WALL_ALL) n++;
            if(originalMap[y][x+1] == WALL_ALL) n++;
            if(originalMap[y][x-1] == WALL_ALL) n++;
            if((n >= 3) && (rand()%5)) {
                originalMap[y][x] = WALL_ALL;
            }
        }
    }
    for(int y = mapH-1; y >= 0; y--) {
        for(int x = mapW-1; x >= 0; x--) {
            if(originalMap[y][x] == WALL_ALL) continue;
            int n = 0;
            if(originalMap[y+1][x] == WALL_ALL) n++;
            if(originalMap[y-1][x] == WALL_ALL) n++;
            if(originalMap[y][x+1] == WALL_ALL) n++;
            if(originalMap[y][x-1] == WALL_ALL) n++;
            if((n >= 3) && (rand()%5)) {
                originalMap[y][x] = WALL_ALL;
            }
        }
    }

// 壁の種類を特定
    CELL_TYPE buff[mapH+2][mapW+2];
    for(int y = 0; y < mapH+2; y++) {
        buff[y][0] = buff[y][mapW+1] = WALL_ALL;
    }
    for(int x = 0; x < mapW+2; x++) {
        buff[0][x] = buff[mapH+1][x] = WALL_ALL;
    }
    for(int y = 0; y < mapH; y++) {
        for(int x = 0; x < mapW; x++) {
            buff[y+1][x+1] = originalMap[y][x];
        }
    }

    for(int y = 0; y < mapH; y++) {
        for(int x = 0; x < mapW; x++) {
            if(buff[y+1][x+1] != WALL_ALL) continue;
            int connect[4] = {0, 0, 0, 0}; // 0:床と接している、1:壁と接している
            int connectWallNum = 0;
            if(buff[y+2][x+1] == WALL_ALL) { // 下
                connect[0] = 1;
                connectWallNum++;
            }
            if(buff[y][x+1] == WALL_ALL) { // 上
                connect[1] = 1;
                connectWallNum++;
            }
            if(buff[y+1][x+2] == WALL_ALL) { // 右
                connect[2] = 1;
                connectWallNum++;
            }
            if(buff[y+1][x] == WALL_ALL) { // 左
                connect[3] = 1;
                connectWallNum++;
            }

            if(connectWallNum == 4) continue;
            else if(connectWallNum == 3) {
                if(connect[0] == 0) originalMap[y][x] = WALL_BOTTOM;
                else if(connect[1] == 0) originalMap[y][x] = WALL_TOP;
                else if(connect[2] == 0) originalMap[y][x] = WALL_RIGHT;
                else if(connect[3] == 0) originalMap[y][x] = WALL_LEFT;
            } else if(connectWallNum == 2) {
                if((connect[0] == 0) && connect[1] == 0) originalMap[y][x] = WALL_SIDE_TB;
                else if((connect[0] == 0) && connect[2] == 0) originalMap[y][x] = WALL_RIGHT_BOTTOM;
                else if((connect[0] == 0) && connect[3] == 0) originalMap[y][x] = WALL_LEFT_BOTTOM;
                else if((connect[1] == 0) && connect[2] == 0) originalMap[y][x] = WALL_RIGHT_TOP;
                else if((connect[1] == 0) && connect[3] == 0) originalMap[y][x] = WALL_LEFT_TOP;
                else if((connect[2] == 0) && connect[3] == 0) originalMap[y][x] = WALL_SIDE_LR;
            } else if(connectWallNum == 1) {
                if(connect[0] == 1) originalMap[y][x] = WALL_END_BOTTOM;
                else if(connect[1] == 1) originalMap[y][x] = WALL_END_TOP;
                else if(connect[2] == 1) originalMap[y][x] = WALL_END_RIGHT;
                else if(connect[3] == 1) originalMap[y][x] = WALL_END_LEFT;
            } else {
                originalMap[y][x] = PILLAR;
            }
        }
    }
    for(int y = 0; y < mapH; y++) {
        for(int x = 0; x < mapW; x++) {
            changedMap[y][x] = originalMap[y][x];
        }
    }

    mapConversion(originalMap);
}
void DungeonManage::initChar() {
    int x = 0, y = 0;
    while((originalMap[y][x] != AISLE && originalMap[y][x] != FLOOR)) {
        x = rand() % mapW;
        y = rand() % mapH;
    }
    player.put(x, y);

    for(auto itr = enemies.begin(); itr < enemies.end(); itr++) {
        while((originalMap[y][x] != AISLE && originalMap[y][x] != FLOOR) || (isPlayerPos(x, y))) {
            x = rand() % mapW;
            y = rand() % mapH;
        }
        enemies.erase(itr);
        enemies.insert(itr, Enemy());
        itr->put(x, y);
    }
}
void DungeonManage::initItem() {
    int x = 0, y = 0;
}

void DungeonManage::input() {
    std::cin >> inputValue;
    switch(inputValue) {
        case 'w': player.move(UP); break;
        case 'a': player.move(LEFT); break;
        case 's': player.move(DOWN); break;
        case 'd': player.move(RIGHT); break;
        case 'q': isRunning = false;
    }
}
void DungeonManage::update() {

}
void DungeonManage::output() {
    std::cout << "  ";
    for(int x = 0; x < mapW; x++)
        std::cout << std::setw(2) << x;
    std::cout << "\n";
    for(int y = 0; y < mapH; y++) {
        std::cout << std::setw(2) << y;
        for(int x = 0; x < mapW; x++) {
            // 実装の際はフロアのバッファの上から重ねて描画する方法で?
            if(isPlayerPos(x, y)) {
                std::cout << player.getIcon();
                continue;
            }
            if(isEnemiesPos(x, y)) {
                std::cout << posToEnemyIcon(x, y) << " ";
                continue;
            }
            std::cout << map[y][x];
        }
        std::cout << "\n";
    }
    // std::cout << "プレイヤーHP" << player.getNowHP() << "/" << player.getMaxHP() << "\n";
    // for(AI &e : enemies) {
    //     std::cout << "敵HP" << e.getNowHP() << "/" << e.getMaxHP() << "\n";
    // }
}
void DungeonManage::quit() {

}

// CELL_TYPEからstringに変換
void DungeonManage::mapConversion(CELL_TYPE originalMap[mapH][mapW]) {
    for(int y = 0; y < mapH; y++)
        for(int x = 0; x < mapW; x++)
            switch(originalMap[y][x]) {
                case NONE:              map[y][x] = "~ "; break;
                case PILLAR:            map[y][x] = "・"; break;
                case WALL_LEFT:         map[y][x] = "｜"; break;
                case WALL_RIGHT:        map[y][x] = "｜"; break;
                case WALL_TOP:          map[y][x] = "￣"; break;
                case WALL_BOTTOM:       map[y][x] = "＿"; break;
                case WALL_LEFT_TOP:     map[y][x] = "⎾ "; break;
                case WALL_LEFT_BOTTOM:  map[y][x] = "⎿ "; break;
                case WALL_RIGHT_TOP:    map[y][x] = "⏋ "; break;
                case WALL_RIGHT_BOTTOM: map[y][x] = "⏌ "; break;
                case WALL_SIDE_LR:      map[y][x] = "||"; break;
                case WALL_SIDE_TB:      map[y][x] = "二"; break;
                case WALL_END_LEFT:     map[y][x] = "］"; break;
                case WALL_END_RIGHT:    map[y][x] = "［"; break;
                case WALL_END_TOP:      map[y][x] = "Ｖ"; break;
                case WALL_END_BOTTOM:   map[y][x] = "Ａ"; break;
                case WALL_ALL:          map[y][x] = "■ "; break;    // Windowsではスーペースはいらない
                case FLOOR: case AISLE: map[y][x] = "  "; break;
                case STEP:              map[y][x] = "S "; break;
            }
}

bool DungeonManage::isPlayerPos(int x, int y) {
    if((x == player.getX()) && (y == player.getY())) return true;
    return false;
}
bool DungeonManage::isEnemiesPos(int x, int y) {
    for(Enemy e : enemies) {
        if((x == e.getX()) && (y == e.getY())) return true;
    }
    return false;
}
std::string DungeonManage::posToEnemyIcon(int x, int y) {
    for(Enemy e : enemies) {
        if((x == e.getX()) && (y == e.getY())) return e.getIcon();
    }
    return "  ";
}