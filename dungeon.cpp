#include <iostream>
#include <random>

#include "AreaDivide.h"

using namespace std;

int main()
{
    random_device seed;
    mt19937 engine(seed());
    uniform_int_distribution<int> rand(1, 100);

    // cout << rand(engine) << endl; 

    initFloor();

    return 0;
}