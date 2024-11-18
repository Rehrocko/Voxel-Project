#include "Chunk.h"

void Chunk::Init() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Position vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	// Material
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

glm::mat4 Chunk::GetModel() {
	// Create and fill vertex array with voxel data
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	auto model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(chunkPos.x * 64, chunkPos.y * 64, chunkPos.z * 64));
	return model;
}

void Chunk::CreateBuffer() {
	float vertexData[CS_P3 * 4 * 36];
	for (int z = 0; z < CS; z++) {
		for (int y = 0; y < CS; y++) {
			for (int x = 0; x < CS; x++) {
				int offset = (x + (y * CS) + (z * CS_2)) * 4 * 36;
				// TODO: Make these x into a cube, so basically a vertex at X, Y, Z, X + 1, Y, Z and the 36 combinations of that
				// Then we are done
				// X
				vertexData[offset + 0] = x;
				// Y
				vertexData[offset + 1] = y;
				// Z
				vertexData[offset + 2] = z;
				// Material
				vertexData[offset + 4 * 36 - 1] = (float)voxels[offset / 4 / 36].material;
			}
		}
	}
}