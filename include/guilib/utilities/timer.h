#ifndef TIMER_H
#define TIMER_H

#include <utilities/libexport.h>
#include <chrono>

namespace GUILib
{
	/**
	* @brief Utility class providing timing functionality.
	*/
	class LIB_DECLSPEC Timer
	{
	public:
		/*
		* @brief This is the default class constructor.
		* The timer is started automatically.
		*/
		Timer();

		~Timer() = default;

		/**
		* @brief Restarts the timer.
		*/
		void Reset();

		/**
		* @brief Returns the time elapsed since timer start.
		* @return Elapsed time in seconds.
		*/
		float GetElapsedTime() const;
	private:
		std::chrono::steady_clock::time_point m_startTime;
	};
}

#endif
