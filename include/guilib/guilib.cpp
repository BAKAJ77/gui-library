#include <guilib.h>
#include <utilities/resource_loader.h>
#include <utilities/input_system.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include <vector>

namespace GUILib
{
	bool InitLibraryGLFWImpl(GLFWwindow* window, GLADloadproc loadProcFunc)
	{
		assert((window != nullptr) && "The GLFW window pointer given is NULL.");
		if (!glfwInit())
			return false;

		if (!gladLoadGLLoader(loadProcFunc)) // Load the addresses of the OpenGL function pointers
			return false;

		// Enable required OpenGL features
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_STENCIL_TEST);
		glEnable(GL_MULTISAMPLE);
		
		// Initialize the Input system
		InputSystem::GetInstance().InitGLFWImpl(window);

		// Initialise the shaders required by the UI components
		ResourceLoader::GetInstance().LoadShadersFromString("Geometry", ResourceConstants::geometryVshSrc, ResourceConstants::geometryFshSrc);
		ResourceLoader::GetInstance().LoadShadersFromString("Text", ResourceConstants::geometryVshSrc, ResourceConstants::textRenderFshSrc);

		/// Initialise the basic geometry required by the UI components ///
		// Square Geometry
		ResourceLoader::Geometry sqGeometry = {
			new VertexBuffer(ResourceConstants::squareVertices, sizeof(ResourceConstants::squareVertices), GL_STATIC_DRAW),
			new IndexBuffer(ResourceConstants::squareIndices, sizeof(ResourceConstants::squareIndices), GL_STATIC_DRAW) 
		};

		sqGeometry.vao = new VertexArray();
		sqGeometry.vao->PushLayout(0, 2, 4 * sizeof(float));
		sqGeometry.vao->PushLayout(1, 2, 4 * sizeof(float), 2 * sizeof(float));
		sqGeometry.vao->AttachBuffers(*sqGeometry.vbo, sqGeometry.ibo);

		ResourceLoader::GetInstance().AddGeometry("Square", sqGeometry);

		// Triangle Geometry
		ResourceLoader::Geometry triGeometry = {
			new VertexBuffer(ResourceConstants::triangleVertices, sizeof(ResourceConstants::triangleVertices), GL_STATIC_DRAW)
		};

		triGeometry.vao = new VertexArray();
		triGeometry.vao->PushLayout(0, 2, 4 * sizeof(float));
		triGeometry.vao->PushLayout(1, 2, 4 * sizeof(float), 2 * sizeof(float));
		triGeometry.vao->AttachBuffers(*triGeometry.vbo);

		ResourceLoader::GetInstance().AddGeometry("Triangle", triGeometry);

		// Line Geometry
		ResourceLoader::Geometry lnGeometry = { 
			new VertexBuffer(ResourceConstants::lineVertices, sizeof(ResourceConstants::squareVertices), GL_STATIC_DRAW) 
		};

		lnGeometry.vao = new VertexArray();
		lnGeometry.vao->PushLayout(0, 2, 4 * sizeof(float));
		lnGeometry.vao->PushLayout(1, 2, 4 * sizeof(float), 2 * sizeof(float));
		lnGeometry.vao->AttachBuffers(*lnGeometry.vbo);

		ResourceLoader::GetInstance().AddGeometry("Line", lnGeometry);

		// Checkmark Geometry
		ResourceLoader::Geometry chkmGeometry = {
			new VertexBuffer(ResourceConstants::checkmarkVertices, sizeof(ResourceConstants::checkmarkVertices), GL_STATIC_DRAW)
		};

		chkmGeometry.vao = new VertexArray();
		chkmGeometry.vao->PushLayout(0, 2, 4 * sizeof(float));
		chkmGeometry.vao->PushLayout(1, 2, 4 * sizeof(float), 2 * sizeof(float));
		chkmGeometry.vao->AttachBuffers(*chkmGeometry.vbo);

		ResourceLoader::GetInstance().AddGeometry("Checkmark", chkmGeometry);

		// Circle Geometry
		std::vector<glm::vec4> circleVertices;
		circleVertices.push_back({ 0.0f, 0.0f, 0.5f, 0.5f });

		for (float angle = 0.0f; angle <= 360.0f; angle += ResourceConstants::circleGeoemtryAngleStep)
		{
			glm::vec2 vertexPos, uvCoord;
			vertexPos = { glm::cos(glm::radians(angle)) / 2.0f, glm::sin(glm::radians(angle)) / 2.0f };
			uvCoord = vertexPos + 0.5f;

			circleVertices.push_back(glm::vec4(vertexPos, uvCoord));
		}

		ResourceLoader::Geometry circGeometry = {
			new VertexBuffer(circleVertices.data(), circleVertices.size() * sizeof(glm::vec4), GL_STATIC_DRAW)
		};

		circGeometry.vao = new VertexArray();
		circGeometry.vao->PushLayout(0, 2, 4 * sizeof(float));
		circGeometry.vao->PushLayout(1, 2, 4 * sizeof(float), 2 * sizeof(float));
		circGeometry.vao->AttachBuffers(*circGeometry.vbo);

		ResourceLoader::GetInstance().AddGeometry("Circle", circGeometry);

		return true;
	}

	void FreeLibrary() { ResourceLoader::GetInstance().FreeResources(); }
}