#include "Dungeon.h"

int main()
{
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<int> randNum(AREA_MAX, 100);

    Dungeon dungeon;
    while(dungeon.isRunning) {
        dungeon.init(randNum(engine));
        dungeon.run();
    }
    dungeon.quit();
    return 0;
}
