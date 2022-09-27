#include "Behavior.h"

namespace engine
{
    void Behavior::SetActive(bool bActive)
    {
        // ���� ���¿� �Ű����� ���°� ���ٸ� �������� �ʴ´�.
        if (IsActive() == bActive)
        {
            return;
        }

        if (bActive)
        {
            GetEngine()->GetBehaviorOnEnableQueue().emplace(this);
        }
        else
        {
            GetEngine()->GetBehaviorOnDisableQueue().emplace(this);
        }

        Component::SetActive(bActive);
    }

    Timer& Behavior::GetTimer()
    {
        return GetEngine()->GetTimer();
    }

    InputManager& Behavior::GetInput()
    {
        return GetEngine()->GetInput();
    }

    void Behavior::addToEventContainer()
    {
        GetEngine()->GetBehaviors().emplace_back(this);
        GetEngine()->GetBehaviorAwakeQueue().emplace(this);
        GetEngine()->GetBehaviorOnEnableQueue().emplace(this);
        GetEngine()->GetBehaviorStartQueue().emplace(this);
    }

    void Behavior::removeFromEventContainer()
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