#pragma once

#include <string>
#include <unordered_map>

#include "Component.h"

class AIComponent : public Component
{
    AIComponent(class Actor* owner);

    void Update() override;
    void ChangeState(const std::string& name);

    void RegisterState(class AIState* state);

private:
    std::unordered_map<std::string, class AIState*> mStateMap;

    class AIState* mCurrentState;
};