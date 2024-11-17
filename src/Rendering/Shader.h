#pragma once
#include "../Common.h"

class Shader {
	public:
		int		ID = -1;
		void	Load(std::string vertexPath, std::string fragmentPath);
		void	Use();
		void	Reload();
		void	SetBool(std::string name, bool value);
		void	SetInt(std::string name, int value);
		void	SetFloat(std::string name, float value);
		void	SetMat4(std::string name, glm::mat4 value);
		void	SetVec3(std::string name, glm::vec3 value);
	private:
		std::string _vertexPath;
		std::string _fragmentPath;
};