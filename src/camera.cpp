#include "camera.h"

glm::mat4 Camera::view() const
{
    return glm::lookAt(glm::vec3(6.0f, 5.0f, 6.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::projection() const
{
    return glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}