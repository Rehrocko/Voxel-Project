#include "Camera.h"

#include "Time.h"
#include "Input.h"

void Camera::CalculateVectors() {
	// calculate the new Front vector
	auto front_ = glm::vec3(0);
	front_.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front_.y = sin(glm::radians(pitch));
	front_.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front_);
	// also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(front, absoluteUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::GetViewMatrix() const {
	return glm::lookAt(position, position + front, up);
}

void Camera::Update() {
	Movement();
	Rotation();
}

void Camera::Movement() {
	float velocity = speed * Time::deltaTime;
	if (Input::KeyDown(GLFW_KEY_W)) position += front	* velocity;
	if (Input::KeyDown(GLFW_KEY_A)) position += -right	* velocity;
	if (Input::KeyDown(GLFW_KEY_S)) position += -front	* velocity;
	if (Input::KeyDown(GLFW_KEY_D)) position += right	* velocity;
}

void Camera::Rotation() {
	yaw		+=	Input::GetMouseOffsetX() * sensitivity;
	pitch	+=	Input::GetMouseOffsetY() * sensitivity;

	yaw = fmod((fmod(yaw + 180.0f, 360.0f) + 360.0f), 360.0f) - 180.0f;
	pitch = std::clamp(pitch, -89.0f, 89.0f);

	CalculateVectors();
}