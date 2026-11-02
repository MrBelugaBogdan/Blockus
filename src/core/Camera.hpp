#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float yaw;
    float pitch;

    Camera(glm::vec3 startPos) {
        position = startPos;
        front = glm::vec3(0.0f, 0.0f, -1.0f);
        up = glm::vec3(0.0f, 1.0f, 0.0f);
        yaw = -90.0f;
        pitch = 0.0f;
    }

    glm::mat4 getViewMatrix() {
        return glm::lookAt(position, position + front, up);
    }

    void processKeyboard(char direction, float deltaTime) {
        float speed = 5.0f * deltaTime;
        if (direction == 'W') position += speed * front;
        if (direction == 'S') position -= speed * front;
        if (direction == 'A') position -= glm::normalize(glm::cross(front, up)) * speed;
        if (direction == 'D') position += glm::normalize(glm::cross(front, up)) * speed;
    }

    void processMouse(float xOffset, float yOffset) {
        float sensitivity = 0.1f;
        yaw += xOffset * sensitivity;
        pitch += yOffset * sensitivity;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(direction);
    }
};
