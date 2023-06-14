#include "generateDungeons/OriginalMethod.h"

using namespace std;

char input;

int main() {
    srand(time(NULL));

    initFloor();

    Original();

    fillSurround();
    randomEraseDeadEnd();
    identificationWallKind();

    arrangementPlayer(areas.size());
    arrangementEnemy(areas.size());
    cout << areas.size() << "\n";

    output();

    return 0;
}