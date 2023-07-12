#include <algorithm>

#include "Actor.h"
#include "Dungeon.h"
#include "Component.h"

Actor::Actor(Dungeon* dungeon)
:mState(Alive)
,mPosition(Vector2::Zero)
,mScale(1.0f)
,mRotation(0.0f)
,mDungeon(dungeon)
{
    mDungeon->AddActor(this);
}

Actor::~Actor()
{
    mDungeon->RemoveActor(this);
    while(!mComponents.empty())
    {
        delete mComponents.back();
    }
}

void Actor::Update()// float deltaTime
{
    if(mState == Alive)
    {
        UpdateComponent();// deltaTime
        UpdateActor();// deltaTime
    }
}

void Actor::UpdateComponents()//float deltaTime
{
    for(auto comp : mComponents)
    {
        comp->Update();//deltaTime
    }
}

void Actor::UpdateActor()//float deltaTime
{

}

void Actor::AddComponent(Component* component)
{
    int myOrder = component->GetUpdateOrder();
    auto iter = mComponent.begin();
    for( ; iter != mComponents.end(); ++iter)
    {
        if(myOrder <(*iter)->GetUpdateOrder())
        {
            break;
        }
    }

    mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if(iter != mComponents.end())
    {
        mComponents.erase(iter);
    }
}