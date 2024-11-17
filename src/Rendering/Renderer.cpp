#include "Renderer.h"

#include "../Engine.h"
#include "../Core/GL.h"

struct Shaders {
	Shader voxel;
} _shaders;

void Renderer::Init() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

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
	float vertices[] = { // honestly i just copied this because it is way to long, this has the vertices of a cube in 3dspace along with the texture coords mapped
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	unsigned int VAO, VBO;
	// Create all the objects
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind them
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Give the buffer our vertices
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Give the vertices their position attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Unbind everything
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// render boxes
	glBindVertexArray(VAO);
	for (unsigned int i = 0; i < 1000; i++)
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		auto model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(rand() % 100, rand() % 100, rand() % 100));
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		_shaders.voxel.SetMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	DeveloperImGUI();
}

void Renderer::DeveloperImGUI() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	bool* open = nullptr;
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(120, 50));
	ImGui::SetNextWindowFocus();
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0, 0, 0, 0));
	if (displayFPS && ImGui::Begin(std::format("FPS: {}", std::round(ImGui::GetIO().Framerate * 10) / 10).c_str(), open, ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground)) {
		ImGui::End();
	}
	ImGui::PopStyleColor();

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