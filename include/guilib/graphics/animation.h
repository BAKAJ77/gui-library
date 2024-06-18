#ifndef ANIMATION_H
#define ANIMATION_H

#include <utilities/libexport.h>
#include <external/glm/glm/glm.hpp>

namespace GUILib
{
	/**
	* @brief Animation method for linearly transitioning a value from the base point to the target point.
	* 
	* @param[in] currentVal - The current value that is being transitioned.
	* @param[in] baseVal - The value of the starting point, where the current value is being transitioned from.
	* @param[in] targetVal - The value of the end point, where the current value is being transitioned to.
	* @param[in] speed - A factor specifying the speed of the transition.
	* @param[in] deltaTime - The time passed between the last frame and the current frame.
	* 
	* @return The new calculated current value.
	*/
	template<typename T>
	static T FadeTo(T currentVal, T baseVal, T targetVal, float speed, float deltaTime)
	{
		const T diff = targetVal - baseVal;

		if (diff >= 0)
			currentVal = std::min(currentVal + (diff * speed * deltaTime), targetVal);
		else
			currentVal = std::max(currentVal + (diff * speed * deltaTime), targetVal);

		return currentVal;
	}

	/**
	* @brief Animation method for linearly transitioning a vector from the base point to the target point.
	*
	* @param[in] currentVal - The vector that is being transitioned.
	* @param[in] baseVal - The vector representing the starting point, this is where the current vector is being transitioned from.
	* @param[in] targetVal - The vector representing the end point, this is where the current vector is being transitioned to.
	* @param[in] speed - A factor specifying the speed of the transition.
	* @param[in] deltaTime - The time passed between the last frame and the current frame.
	*
	* @return The new calculated vector.
	*/
	template<>
	static glm::vec2 FadeTo<glm::vec2>(glm::vec2 currentVal, glm::vec2 baseVal, glm::vec2 targetVal, float speed, float deltaTime)
	{
		currentVal.x = FadeTo<double>(currentVal.x, baseVal.x, targetVal.x, speed, deltaTime);
		currentVal.y = FadeTo<double>(currentVal.y, baseVal.y, targetVal.y, speed, deltaTime);
		return currentVal;
	}

	/**
	* @brief Animation method for linearly transitioning a vector from the base point to the target point.
	*
	* @param[in] currentVal - The vector that is being transitioned.
	* @param[in] baseVal - The vector representing the starting point, this is where the current vector is being transitioned from.
	* @param[in] targetVal - The vector representing the end point, this is where the current vector is being transitioned to.
	* @param[in] speed - A factor specifying the speed of the transition.
	* @param[in] deltaTime - The time passed between the last frame and the current frame.
	*
	* @return The new calculated vector.
	*/
	template<>
	static glm::vec3 FadeTo<glm::vec3>(glm::vec3 currentVal, glm::vec3 baseVal, glm::vec3 targetVal, float speed, float deltaTime)
	{
		currentVal.x = FadeTo<double>(currentVal.x, baseVal.x, targetVal.x, speed, deltaTime);
		currentVal.y = FadeTo<double>(currentVal.y, baseVal.y, targetVal.y, speed, deltaTime);
		currentVal.z = FadeTo<double>(currentVal.z, baseVal.z, targetVal.z, speed, deltaTime);
		return currentVal;
	}

	/**
	* @brief Animation method for linearly transitioning a vector from the base point to the target point.
	*
	* @param[in] currentVal - The vector that is being transitioned.
	* @param[in] baseVal - The vector representing the starting point, this is where the current vector is being transitioned from.
	* @param[in] targetVal - The vector representing the end point, this is where the current vector is being transitioned to.
	* @param[in] speed - A factor specifying the speed of the transition.
	* @param[in] deltaTime - The time passed between the last frame and the current frame.
	*
	* @return The new calculated vector.
	*/
	template<>
	static glm::vec4 FadeTo<glm::vec4>(glm::vec4 currentVal, glm::vec4 baseVal, glm::vec4 targetVal, float speed, float deltaTime)
	{
		currentVal.x = FadeTo<double>(currentVal.x, baseVal.x, targetVal.x, speed, deltaTime);
		currentVal.y = FadeTo<double>(currentVal.y, baseVal.y, targetVal.y, speed, deltaTime);
		currentVal.z = FadeTo<double>(currentVal.z, baseVal.z, targetVal.z, speed, deltaTime);
		currentVal.w = FadeTo<double>(currentVal.w, baseVal.w, targetVal.w, speed, deltaTime);
		return currentVal;
	}
}

#endif