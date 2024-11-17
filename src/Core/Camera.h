#pragma once

#include "../Common.h"

// Default camera values
const float yaw_ = -90.0f;
const float pitch_ = 0.0f;
const float speed_ = 2.5f;
const float sensitivity_ = 0.07f;
const float zoom_ = 45.0f;

struct Camera {
	glm::vec3 position;
	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 front = glm::vec3(0, 0, -1);
	glm::vec3 right = glm::vec3(0, 0, 0);
	glm::vec3 absoluteUp = glm::vec3(0, 1, 0);
	
	float yaw;
	float pitch;

	float speed;
	float sensitivity;
	float zoom;

	bool render = true;

	Camera(glm::vec3 position = glm::vec3(0, 0, 0), float yaw = yaw_, float pitch = pitch_, float speed = speed_, float sensitivity = sensitivity_, float zoom = zoom_) :
		position(position),
		yaw(yaw),
		pitch(pitch),
		speed(speed),
		sensitivity(sensitivity),
		zoom(zoom)
		{ CalculateVectors(); }

	void		CalculateVectors();
	glm::mat4	GetViewMatrix() const;
	void		Update();
	void		Movement();
	void		Rotation();
};