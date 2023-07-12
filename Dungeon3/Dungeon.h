#pragma once

#include <vector>

#include "Map.h"

class Dungeon {
public:
    Dungeon();
    bool Initialize();
    void RunLoop();
    void ShutDown();

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    CELL_TYPE originalMap[mapH][mapW];
    CELL_TYPE changedMap[mapH][mapW];

private:
    void LoadData();
    int GenerateDungeon();
    void CreateActor(int roomCount);

    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    void UnloadData();

    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;

    bool mIsRunning;
    bool mUpdatingActors;
    char input;

    class Player* mPlayer;
};