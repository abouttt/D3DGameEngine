#include "UI.h"
#include "GameEngine.h"

namespace engine 
{
    void UI::addToEventContainer()
    {
        GetEngine()->GetUIs().emplace_back(this);
    }

    void UI::removeFromEventContainer()
    {
        auto it = std::find(GetEngine()->UIBegin(), GetEngine()->UIEnd(), this);
        if (it != GetEngine()->UIEnd())
        {
            GetEngine()->GetUIs().erase(it);
        }
    }
}