#include "Behavior.h"

namespace engine
{
    Behavior::~Behavior()
    {
        auto it = find(GetEngine()->BehaviorBegin(), GetEngine()->BehaviorEnd(), this);
        if (it != GetEngine()->BehaviorEnd())
        {
            GetEngine()->GetBehaviors().erase(it);
        }
    }

    Timer& Behavior::GetTimer()
    {
        return GetEngine()->GetTimer();
    }

    InputManager& Behavior::GetInput()
    {
        return GetEngine()->GetInput();
    }

    void Behavior::addToComponentPtrContainer()
    {
        GetEngine()->GetBehaviors().emplace_back(this);
        GetEngine()->GetBehaviorStartQueue().emplace(this);
    }
}