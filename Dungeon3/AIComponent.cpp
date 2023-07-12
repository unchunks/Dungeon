#include "AIComponent.h"

#include "AIState.h"

AIComponent::AIComponent(class Actor* owner)
:Component(owner, 10)
{

}

void AIComponent::Update() 
{
    if(mCurrentState)
    {
        mCurrentState->Update();
    }
}

void AIComponent::ChangeState(const std::string& name)
{

}

void AIComponent::RegisterState(AIState* state)
{
    mStateMap.emplace(state->GetName(), state);
}