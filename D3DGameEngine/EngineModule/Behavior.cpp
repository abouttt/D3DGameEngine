#include "Behavior.h"

namespace engine
{
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

    void Behavior::removeFromComponentPtrContainer()
    {
        auto it = find(GetEngine()->BehaviorBegin(), GetEngine()->BehaviorEnd(), this);
        if (it != GetEngine()->BehaviorEnd())
        {
            GetEngine()->GetBehaviors().erase(it);
        }

        std::shared_ptr<Behavior> temp = shared_from_this();
        GetEngine()->GetBehaviorOnDestroyQueue().emplace(std::move(temp));
    }
}