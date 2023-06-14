#include "AreaDivisionMethod.h"

using namespace std;

int areaCount = 0;
int randomNumber;
char input;

int main() {
    srand(time(NULL));
    randomNumber = rand();
    areas[0] = Area(0, 0, FLOOR_W, FLOOR_H);
    areaCount = 1;
    initFloor();

    AreaDivision();

    fillSurround();
    randomEraseDeadEnd();
    identificationWallKind();

    arrangementPlayer(areaCount);
    arrangementEnemy(areaCount);
    cout << areaCount << " : " << areas.size() << "\n";

    output();

    return 0;
}