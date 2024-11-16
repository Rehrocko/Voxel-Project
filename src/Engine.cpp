// Basically main.cpp except sounds cooler and has a header file

#include "Engine.h"

namespace Engine
{

	// Game Logic Functions
	
	void Initialize()
	{

		GL::Init(960, 540);

		Time	::	Init();
		Input	::	Init();

		// Start update cycle
		Update();

	}
	void Update()
	{
		while (GL::WindowIsOpen() && GL::WindowHasNotBeenForceClosed()) {
			GL::ClearScreen(glm::vec4(0.1f), GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			GL::ProcessInput();
			
			Time	::	Update();
			Input	::	Update();

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
		if (Input::KeyPressed(GLFW_KEY_O)) {
			openDevMenu = !openDevMenu;
		}
	}

	// Developer Functions
	
	void DeveloperImGUI()
	{
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

		int settingsWidth = 150;

		ImGui::SetNextWindowPos(ImVec2(GL::GetWindowWidth() - settingsWidth, 0));
		ImGui::SetNextWindowSize(ImVec2(settingsWidth, GL::GetWindowHeight() / 4));
		if (openDevMenu && ImGui::Begin("Settings", open, ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar)) {
			ImGui::Checkbox("Show FPS", &displayFPS);
			ImGui::End();
		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}