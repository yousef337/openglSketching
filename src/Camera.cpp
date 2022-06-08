#include "Camera.h"

Camera::Camera(){
    using namespace glm;
    view = mat4(1.0f);
    Camera::pointingPos = vec3(0.0f, 0.0f, 2.0f);
    cameraPos = vec3(0.0f, 1.0f, -4.0f);
    upDir = vec3(0.0f, 1.0f, 0.0f);
    deltaTime = 0.0f;
    lastFrame = 0.0f;


}

void Camera::keyboardProcessing(GLFWwindow* window){
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    const float cameraSpeed = 15.5f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        cameraPos += cameraSpeed * pointingPos;
    }else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        cameraPos -= cameraSpeed * pointingPos;
    }else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        cameraPos -= glm::normalize(glm::cross(pointingPos, upDir)) * cameraSpeed;
    }else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        cameraPos += glm::normalize(glm::cross(pointingPos, upDir)) * cameraSpeed;
    }
}


glm::mat4 Camera::getViewMatrix() const{
    return glm::lookAt(cameraPos, cameraPos + pointingPos, upDir);
}

void Camera::setPointingPosition(glm::vec3 pointingPos){
    this->pointingPos = pointingPos;
}

