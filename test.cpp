#include "AreaDivide.h"
#include <glm/glm.hpp>

AreaDivide areaDivide;

glm::vec2 getRandomPos(int roomCount)
{
    int roomNum = rand() % roomCount;
    Room room = areaDivide.getRoom(roomNum);
    glm::vec2 pos;
    pos.x = room.x + rand()%room.w;
    pos.y = room.y + rand()%room.h;
    return pos;
}

// TODO: AStarのテスト

int main() {
    areaDivide.initFloor();
    areaDivide.generate();
    areaDivide.fillSurround();
    areaDivide.randomEraseDeadEnd();
    areaDivide.identificationWallKind();

    glm::vec2 goal = getRandomPos(areaDivide.areaCount);
    std::cout << "GOAL ==> (" << goal.x << ", " << goal.y << ")\n";
    route = Astar(dungeon, 0, mPos.x, mPos.y, goal.x, goal.y);
    for(auto pos: route)
    {
        std::cout << "(" << pos.x << ", " << pos.y << ")\n";
    }
}