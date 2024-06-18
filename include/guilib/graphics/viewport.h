#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <utilities/libexport.h>
#include <external/glm/glm/glm.hpp>

namespace GUILib
{
	/** 
	* @brief This is a class detailing the space where user interface elements are rendered into. 
	*/
	class LIB_DECLSPEC Viewport
	{
	public:
		/**
		* @brief This is a default class constructor method.
		* By default, the position of the viewport is set to (0,0) and the size is set to (600,600).
		*/
		Viewport();

		/**
		* @brief This is a class constructor method.
		* 
		* @param[in] pos - The position to assign to the viewport.
		* @param[in] size - The size to assign to the viewport.
		*/
		Viewport(glm::ivec2 pos, glm::ivec2 size);

		~Viewport() = default;

		/**
		 * @brief Sets the position of the viewport.
		 * @param[in] pos - The new position of the viewport.
		 */
		void SetPosition(glm::ivec2 pos);

		/**
		 * @brief Sets the size (in pixels) of the viewport.
		 * @param[in] size - The new size of the viewport.
		 */
		void SetSize(glm::ivec2 size);

		/**
		* @brief Updates the OpenGL rendering viewport based on the stored viewport data.
		*/
		void Update();
		
		/**
		* @brief Returns the matrix generated by the viewport.
		* @return A 4x4 matrix representing the viewport camera.
		*/
		const glm::mat4& GetMatrix() const;

		/**
		* @brief Returns the current position of the viewport.
		* @return A 2-dimensional vector respresenting the position of the viewport.
		*/
		const glm::ivec2& GetPosition() const;

		/**
		* @brief Returns the current size of the viewport.
		* @return A 2-dimensional vector respresenting the size of the viewport.
		*/
		const glm::ivec2& GetSize() const;
	private:
		glm::ivec2 m_position, m_size;
		glm::mat4 m_matrix;
		bool m_changed;
	};
}

#endif