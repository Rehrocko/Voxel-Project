#pragma once

#include "Voxel.h"

// CS = chunk size (max 62)
static constexpr int CS = 62;

// Padded chunk size
static constexpr int CS_P = CS + 2;
static constexpr int CS_2 = CS * CS;
static constexpr int CS_P2 = CS_P * CS_P;
static constexpr int CS_P3 = CS_P * CS_P * CS_P;

struct Chunk {
	Voxel voxels[CS_P3];
	glm::vec3 chunkPos = glm::vec3(0);
	Chunk(int VAO = 0, int VBO = 0) : VAO(VAO), VBO(VBO) {
		memset(voxels, 0, CS_P3 * sizeof(Voxel));
		Init();
	}
	unsigned int VAO, VBO;

	void		Init();
	glm::mat4	GetModel();
	void		CreateBuffer();
};