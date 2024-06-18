#include <utilities/timer.h>

namespace GUILib
{
	Timer::Timer() { this->Reset(); }

	void Timer::Reset()
	{
		m_startTime = std::chrono::high_resolution_clock::now();
	}

	float Timer::GetElapsedTime() const
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		const std::chrono::duration<float> duration = currentTime - m_startTime;
		return duration.count();
	}
}