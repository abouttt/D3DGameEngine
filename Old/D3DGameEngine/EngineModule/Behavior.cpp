#include "Behavior.h"

namespace engine
{
	Behavior::Behavior()
		: mbStart(false)
	{}

	bool Behavior::IsStart() const
	{
		return mbStart;
	}

	void Behavior::SetStart(bool bStart)
	{
		mbStart = bStart;
	}

	GameEngine& Behavior::GetEngine()
	{
		return *GetGameEngine();
	}

	InputManager& Behavior::GetInput()
	{
		return GetGameEngine()->GetInput();
	}

	Timer& Behavior::GetTimer()
	{
		return GetGameEngine()->GetTimer();
	}
}
