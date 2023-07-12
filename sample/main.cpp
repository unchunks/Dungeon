#include "Dungeon.h"

int main() {
    Dungeon dungeon;
    bool success = dungeon.Initialize();
    while(success) {
        dungeon.RunLoop();
    }
    dungeon.ShutDown();
    return 0;
}