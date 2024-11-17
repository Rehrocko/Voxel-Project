// Basically main.cpp except sounds cooler and has a header file

#include "Engine.h"

#include "Rendering/Shader.h"
#include "Core/GL.h"
#include "Core/Time.h"
#include "Core/Input.h"
#include "Core/Scene.h"

namespace Engine
{
	
	std::vector<Scene> _scenes = { Scene() };

	// mainScene really just means working scene, I also just wanted to have a vector of
	// scenes in case I ever needed it, we basically only use mainScene
	Scene& mainScene = _scenes[0];

	// Game Logic Functions
	
	void Initialize() {

		GL::Init(960, 540);
		
		mainScene.Init();

		Time	::	Init();
		Input	::	Init();

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

			DeveloperImGUI();
			QuickKeys();
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
			openDevMenu = !openDevMenu;
		if (Input::KeyPressed(GLFW_KEY_C))
			displayFPS = !displayFPS;
	}

	// Developer Functions
	
	void DeveloperImGUI() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		bool* open = nullptr;
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(120, 50));
		if (displayFPS && ImGui::Begin("FPS", open, ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse)) {
			ImGui::Text(std::to_string(ImGui::GetIO().Framerate).c_str());
			ImGui::End();
		}

		int settingsWidth = 300;

		ImGui::SetNextWindowPos(ImVec2(GL::GetWindowWidth() - settingsWidth, 0));
		ImGui::SetNextWindowSize(ImVec2(settingsWidth, GL::GetWindowHeight() / 4));
		if (openDevMenu && ImGui::Begin("Settings", open, ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar)) {
			Camera mainCamera = mainScene._cameras[0];
			std::string mainCameraYaw = std::format("Yaw: {}", mainCamera.yaw);
			std::string mainCameraPitch = std::format("Pitch: {}", mainCamera.pitch);
			std::string mainCameraPosition = std::format("Position: {}", glm::to_string(mainCamera.position));
			ImGui::Text(mainCameraYaw.c_str());
			ImGui::Text(mainCameraPitch.c_str());
			ImGui::Text(mainCameraPosition.c_str());
			ImGui::End();
		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}