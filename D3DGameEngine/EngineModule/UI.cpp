#include "UI.h"
#include "GameEngine.h"

namespace engine 
{
    UI::~UI()
    {
        auto it = std::find(GetEngine()->UIBegin(), GetEngine()->UIEnd(), this);
        if (it != GetEngine()->UIEnd())
        {
            GetEngine()->GetUIs().erase(it);
        }
    }

    void UI::addToComponentPtrContainer()
    {
        GetEngine()->GetUIs().emplace_back(this);
    }
}