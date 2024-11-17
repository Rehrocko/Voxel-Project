// Basically main.cpp except sounds cooler and has a header file

#include "Engine.h"

#include "Rendering/Shader.h"
#include "Core/GL.h"
#include "Core/Time.h"
#include "Core/Input.h"
#include "Core/Scene.h"
#include "Rendering/Renderer.h"

namespace Engine
{
	// Game Logic Functions
	
	void Initialize() {

		GL::Init(960, 540);
		
		mainScene.Init();

		Time	::	Init();
		Input	::	Init();
		Renderer::	Init();

		// Start update cycle
		Update();

	}
	void Update() {
		while (GL::WindowIsOpen() && GL::WindowHasNotBeenForceClosed()) {
			GL::ClearScreen(glm::vec4(0.1f), GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			GL::ProcessInput();
			
			Time	::	Update();
			Input	::	Update();

			mainScene.Update();

			Renderer::RenderFrame();

			QuickKeys();
			GL::SetScrollOffset(0);
			GL::SwapBuffersPollEvents();
		}
		GL::Terminate();
	}

	void QuickKeys() {
		if (Input::KeyPressed(GLFW_KEY_F))
			GL::ToggleFullscreen();
		if (Input::KeyPressed(GLFW_KEY_Z))
			GL::ToggleCursor();
		if (Input::KeyPressed(GLFW_KEY_O))
			Renderer::openDevMenu = !Renderer::openDevMenu;
		if (Input::KeyPressed(GLFW_KEY_C))
			Renderer::displayFPS = !Renderer::displayFPS;
	}
}