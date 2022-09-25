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
}