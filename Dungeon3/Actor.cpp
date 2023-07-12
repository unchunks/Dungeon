#include <algorithm>

#include "Actor.h"
#include "Dungeon.h"
#include "Component.h"

Actor::Actor(Dungeon* dungeon)
:mState(Alive)
,mPosition(Vector2::Zero)
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

void Actor::Update()
{
    if(mState == Alive)
    {
        UpdateComponents();
        UpdateActor();
    }
}

void Actor::UpdateComponents()
{
    for(auto comp : mComponents)
    {
        comp->Update();
    }
}

void Actor::UpdateActor()
{

}

void Actor::AddComponent(Component* component)
{
    int myOrder = component->GetUpdateOrder();
    auto iter = mComponents.begin();
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