#include "Timer.h"

namespace engine
{

	void Timer::Init()
	{
		mCyclesPerMilliSeconds = getCyclesPerMilliSeconds();
	}

	float Timer::GetElapsedTime() const
	{
		return mElapsedTime;
	}

	float Timer::GetDeltaTime()const
	{
		return mFrameTime / 1000.f;
	}

	float Timer::GetFrameFPS() const
	{
		return mFrameFPS;
	}

	void Timer::BeginTimer()
	{
		mFrameTimeStamp = getCurrentTimeStamp();
		if (mFrameCount == 0)
		{
			mStartTimeStamp = mFrameTimeStamp;
		}
	}

	void Timer::EndTimer()
	{
		mFrameCount++;
		INT64 currentTimeStamp = getCurrentTimeStamp();
		INT64 frameCycles = currentTimeStamp - mFrameTimeStamp;
		INT64 elapsedCycles = currentTimeStamp - mStartTimeStamp;
		mFrameTime = frameCycles / mCyclesPerMilliSeconds;
		mElapsedTime = elapsedCycles / mCyclesPerMilliSeconds;
		mFrameFPS = mFrameTime == 0.f ? 0.f : 1000.f / mFrameTime;
		mAverageFPS = mElapsedTime == 0.f ? 0.f : 1000.f / mElapsedTime * mFrameCount;
	}

	float Timer::getCyclesPerMilliSeconds()
	{
		LARGE_INTEGER frequency;
		if (!QueryPerformanceFrequency(&frequency))
		{
			return 0.f;
		}

		return static_cast<float>(frequency.QuadPart / 1000.f);
	}

	long long Timer::getCurrentTimeStamp()
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		return currentTime.QuadPart;
	}

}