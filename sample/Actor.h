#pragma once

#include <vector>

#include "Math.h"

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

    void Update();//float deltaTime
    void UpdateComponents();//float deltaTime
    virtual void UpdateActor();//float deltaTime

    const Vector2& GetPosition() const { return mPosition; }
    void SetPosition(const Vector2& pos) { mPosition = pos; }
    float GetScale() const { return mScale; }
    void SetScale(float scale) { mScale = scale; }
    float GetRotation() const { return mRotation; }
    void SetRotation(float rotation) { mRotation = rotation; }

    State GetState() const { return mState; }
    void SetState(State state) { mState = state; }

    class Dungeon* GetDungeon() { return mDungeon; }

    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);
private:
    State mState;

    Vector2 mPosition;
    float mScale;
    float mRotation;

    std::vector<class Component*> mComponents;
    class Dungeon* Dungeon;
}