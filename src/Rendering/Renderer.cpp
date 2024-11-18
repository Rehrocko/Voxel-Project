#include "Renderer.h"

#include "../Engine.h"
#include "../Core/GL.h"

struct Shaders {
	Shader voxel;
} _shaders;

void Renderer::Init() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	chunk.voxels[5].material = Material::DIRT;
	chunk.CreateBuffer();

	ReloadShaders();
}

void Renderer::ReloadShaders() {
	std::cout << "Reloading Shaders";
	
	_shaders.voxel.Load("res/shaders/voxel.vert", "res/shaders/voxel.frag");
}

void Renderer::RenderFrame() {
	_shaders.voxel.Use();
	Camera camera = Engine::mainScene._cameras[0];
	glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)GL::GetWindowWidth() / (float)GL::GetWindowHeight(), NEAR_PLANE, FAR_PLANE);
	glm::mat4 viewMatrix = camera.GetViewMatrix();
	glm::vec3 viewPos = camera.position;
	_shaders.voxel.SetMat4("view", viewMatrix);
	_shaders.voxel.SetMat4("projection", projection);
	_shaders.voxel.SetVec3("viewPos", viewPos);
	
	_shaders.voxel.SetMat4("model", chunk.GetModel());

	if (showUI) DeveloperImGUI();
}

void Renderer::DeveloperImGUI() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	bool* open = nullptr;
	ImGui::SetNextWindowPos(ImVec2(0, -6));
	ImGui::SetNextWindowSize(ImVec2(240, 50));
	ImGui::SetNextWindowFocus();
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5.0f, 18.0f));
	if (displayFPS && ImGui::Begin(std::format("FPS: {}\nV-Sync enabled: {}",
												std::round(ImGui::GetIO().Framerate * 10) / 10,
												GL::VSyncIsEnabled()).c_str(),
									open,
									ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground)) {
		ImGui::End();
	}
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();

	int settingsWidth = 360;

	ImGui::SetNextWindowPos(ImVec2(GL::GetWindowWidth() - settingsWidth, 0));
	ImGui::SetNextWindowSize(ImVec2(settingsWidth, GL::GetWindowHeight() / 4));
	if (openDevMenu && ImGui::Begin("Settings", open, ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar)) {
		Camera mainCamera = Engine::mainScene._cameras[0];
		std::string mainCameraYaw = std::format("Yaw: {}", mainCamera.yaw);
		std::string mainCameraPitch = std::format("Pitch: {}", mainCamera.pitch);
		std::string mainCameraPosition = std::format("Position: {}", glm::to_string(mainCamera.position));
		std::string mainCameraSpeed = std::format("Speed: {}", mainCamera.speed);
		ImGui::Text(mainCameraYaw.c_str());
		ImGui::Text(mainCameraPitch.c_str());
		ImGui::Text(mainCameraPosition.c_str());
		ImGui::Text(mainCameraSpeed.c_str());
		ImGui::End();
	}
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}