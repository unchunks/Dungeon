#pragma once

#include <vector>

#include "Math.h"
#include "Map.h"

class Actor
{
public:
    enum State
    {
        Alive,
        Paused,
        Dead
    };
    enum Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    Actor(class Dungeon* dungeon);
    virtual ~Actor();

    void Update();
    void UpdateComponents();
    virtual void UpdateActor() = 0;

    const Vector2& GetPosition() const { return mPosition; }
    void SetPosition(const Vector2& pos) { mPosition = Vector2(pos); }

    State GetState() const { return mState; }
    void SetState(State state) { mState = state; }

    class Dungeon* GetDungeon() { return mDungeon; }

    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);

protected:
    virtual bool CanMoveTo(const Vector2& pos) = 0;

private:
    State mState;

    Vector2 mPosition;

    std::vector<class Component*> mComponents;
    class Dungeon* mDungeon;
};