#include <iostream>

#include "DungeonManage.h"

int main() {
    srand(time(NULL));

    DungeonManage dm;

    dm.generate();
    dm.initChar();
    dm.initItem();

    dm.output();

    while(dm.getIsRunning()) {
        dm.input();
        dm.update();
        dm.output();
    }

    dm.quit();

    return 0;
}