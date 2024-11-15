#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>

#define NEAR_PLANE 0.5f
#define FAR_PLANE 50.0f

// Normal people colors
#define BLACK   glm::vec3(0,0,0)
#define WHITE   glm::vec3(1,1,1)
#define RED     glm::vec3(1,0,0)
#define GREEN   glm::vec3(0,1,0)
#define BLUE    glm::vec3(0,0,1)
#define YELLOW  glm::vec3(1,1,0)
#define PURPLE  glm::vec3(1,0,1)
#define GREY    glm::vec3(0.25f)
// ImGUI colors
#define IMCBLACK  ImColor(0, 0, 0, 255)
#define IMCWHITE  ImColor(255, 255, 255, 255)
#define IMCRED    ImColor(255, 0, 0, 255)
#define IMCGREEN  ImColor(0, 255, 0, 255)
#define IMCBLUE   ImColor(0, 0, 255, 255)
#define IMCYELLOW ImColor(255, 255, 0, 255)
#define IMCPURPLE ImColor(255, 0, 255, 255)
#define IMCGREY   ImColor(50, 50, 50, 255)

namespace Util {
    inline std::string ReadTextFromFile(std::string& path) {
        std::ifstream file(path);
        std::string _string;
        std::string line;
        while (std::getline(file, line)) {
            _string += line + "\n";
        }
        return _string;
    }
}