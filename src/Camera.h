#pragma once
#include "external/glm/vec4.hpp"
#include "external/glm/mat4x4.hpp"
#include "external/glm/ext/matrix_transform.hpp"
#include "external/glm/ext/matrix_clip_space.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Camera {

private:
    glm::mat4 view;
    glm::mat4 proj;
    glm::vec3 pointingPos;
    glm::vec3 cameraPos;
    glm::vec3 upDir;
    float deltaTime;
    float lastFrame;

public:
    Camera();
    void setUpMouseHandler(GLFWwindow* window);
    void keyboardProcessing(GLFWwindow* window);
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjMatrix() const;
    void setPointingPosition(glm::vec3 pointingPos);


};
