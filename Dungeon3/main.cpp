#include "Dungeon.h"

int main() {
    Dungeon dungeon;
    bool success = dungeon.Initialize();
    if(success) {
        dungeon.RunLoop();
    }
    dungeon.ShutDown();
    return 0;
}