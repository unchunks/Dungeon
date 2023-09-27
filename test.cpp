#include "AreaDivide.h"
#include "Player.h"
#include <glm/glm.hpp>
#include <iostream>

AreaDivide areaDivide;
Player player(0, 0, 0, 0, 0);
std::vector<Enemy> enemies = std::vector<Enemy>(NUM_ENEMY, Enemy(SLIME));
CELL_TYPE floorTYPE[FLOOR_H][FLOOR_W];

glm::vec2 getRandomPos(int roomCount)
{
    int roomNum = rand() % roomCount;
    Room room = areaDivide.getRoom(roomNum);
    glm::vec2 pos;
    pos.x = room.x + rand()%room.x;
    pos.y = room.y + rand()%room.y;
    return pos;
}

// AStarのテスト

void out()
{
    bool charDrawn = false;
	for(int y = 0; y < FLOOR_H; y++){
		// for(int x = 0; x < FLOOR_W; x++){
        //     switch(data[y][x].parent)
        //     {
        //         case LEFT: std::cout << "←"; break;
        //         case RIGHT: std::cout << "→"; break;
        //         case UP: std::cout << "↑"; break;
        //         case DOWN: std::cout << "↓"; break;
        //         default: std::cout << " ";
        //     }
        // }

        // std::cout << " | ";

        // for(int x = 0; x < FLOOR_W; x++){
        //     std::cout << data[y][x].status;
        // }

        // std::cout << " | ";

        for(int x = 0; x < FLOOR_W; x++){
            std::cout << floorTYPE[y][x];
            // charDrawn = false;
            // // SDLでは後ろから重ねて描画する
            // if((player.getX() == x) && (player.getY() == y)) {
            //     std::cout << "@";
            //     charDrawn = true;
            // }
            // for(auto e : enemies) {
            //     if((e.getX() == x) && (e.getY() == y)) {
            //         std::cout << "E";
            //         charDrawn = true;
            //     }
            // }
            // if(charDrawn)
            //     continue;
            // switch(floorTYPE[y][x]) {
            //     case NONE:              std::cout << " "; break;
            //     case PILLAR:            std::cout << "W"; break;
            //     case WALL_LEFT:         std::cout << "W"; break;
            //     case WALL_RIGHT:        std::cout << "W"; break;
            //     case WALL_TOP:          std::cout << "W"; break;
            //     case WALL_BOTTOM:       std::cout << "W"; break;
            //     case WALL_LEFT_TOP:     std::cout << "W"; break;
            //     case WALL_LEFT_BOTTOM:  std::cout << "W"; break;
            //     case WALL_RIGHT_TOP:    std::cout << "W"; break;
            //     case WALL_RIGHT_BOTTOM: std::cout << "W"; break;
            //     case WALL_SIDE_LR:      std::cout << "W"; break;
            //     case WALL_SIDE_TB:      std::cout << "W"; break;
            //     case WALL_END_LEFT:     std::cout << "W"; break;
            //     case WALL_END_RIGHT:    std::cout << "W"; break;
            //     case WALL_END_TOP:      std::cout << "W"; break;
            //     case WALL_END_BOTTOM:   std::cout << "W"; break;
            //     case WALL_ALL:          std::cout << "W"; break;
            //     case FLOOR: case AISLE: std::cout << " "; break;
            //     case STEP:              std::cout << "S"; break;
            // }
		}
		std::cout << std::endl;
	}
}

int main() {
    areaDivide.initFloor();
    areaDivide.generate(82);
    areaDivide.fillSurround();
    areaDivide.randomEraseDeadEnd();
    areaDivide.identificationWallKind();

    for(int y = 0; y < FLOOR_H; y++)
        for(int x = 0; x < FLOOR_W; x++)
            floorTYPE[y][x] = areaDivide.buff[y+1][x+1];

    char input;
    while(input != 'q') {
        glm::vec2 start = getRandomPos(areaDivide.getRoomNum());
        player.setPos(start);
        std::cout << "START ==> (" << start.x << ", " << start.y << ")\n";

        glm::vec2 goal = getRandomPos(areaDivide.getRoomNum());
        enemies[0].setPos(goal);
        std::cout << "GOAL ==> (" << goal.x << ", " << goal.y << ")\n";

        std::deque<glm::vec2> x = AStar(areaDivide.getFloor(), start, goal);
        out();
        // for(auto pos: x)
        // {
        //     std::cout << "(" << pos.x << ", " << pos.y << ")\n";
        // }
        std::cin >> input;
    }
}