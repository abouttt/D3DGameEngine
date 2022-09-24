#pragma once

#include <Windows.h>

namespace engine
{
	class Timer
	{
	public:
		Timer() = default;

	public:
		void Init();

		float GetElapsedTime() const;
		float GetDeltaTime() const;
		float GetFrameFPS() const;

		void BeginTimer();
		void EndTimer();

	private:
		float getCyclesPerMilliSeconds();
		long long getCurrentTimeStamp();

	public:
		float mCyclesPerMilliSeconds;
		long long mStartTimeStamp;
		long long mFrameTimeStamp;
		long mFrameCount;
		float mFrameTime;
		float mElapsedTime;
		float mAverageFPS;
		float mFrameFPS;
	};
}
