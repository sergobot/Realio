/**
 * This file is part of Realio.
 * Realio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2015 Sergey Popov <sergobot@vivaldi.net>
**/

#ifndef RCAMERA_H
#define RCAMERA_H

//GLEW
#include <GL/glew.h>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//SDL2
#include <SDL2/SDL.h>

namespace Realio {
// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  3.0f;
const float SENSITIVITY =  0.25f;
const float ZOOM        =  45.0f;

enum RCameraMoveDirection {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

enum RCameraProjectionType {
    ORTHOGONAL,
    PERSPECTIVE
};

class RCamera
{
public:
    RCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
            float yaw = YAW, float pitch = PITCH);
    ~RCamera();

    /**
     * @brief returns current view matrix.
     * @param void.
     * @return current view matrix 4x4.
     */
    glm::mat4 getViewMatrix();

    /**
     * @brief resets camera's attributes.
     * @param void.
     * @return void.
     */
    void reset();

    /**
     * @brief moves the camera.
     * @param direction and delta time.
     * @return void.
     */
    void move(const RCameraMoveDirection direction, const float deltaTime);

    /**
     * @brief rotates the camera.
     * @param x and y axis' offsets.
     * @return void.
     */
    void processMouseMovement(const float xoffset, const float yoffset, const bool constrainPitch = true);

    /**
     * @brief zooms camera's view.
     * @param ratio of zoom.
     * @return void.
     */
    void zoom(const float ratio);

    /**
     * @brief returns current zoom ratio.
     * @param void.
     * @return float.
     */
    float getZoomRatio();

    /**
     * @brief sets movement speed of the camera.
     * @param new speed in float.
     * @return void.
     */
    void setMovementSpeed(const float speed);

    /**
     * @brief returns movement speed of the camera.
     * @param void.
     * @return current movement speed in float.
     */
    float getMovementSpeed();

    static RCamera* global;

private:
    // Camera Attributes
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;

    // Eular Angles
    float m_yaw;
    float m_pitch;

    // Camera options
    float m_movementSpeed;
    float m_mouseSensitivity;
    float m_zoom;

    /**
     * @brief updates all the camera vectors.
     * @param void.
     * @return void.
     */
    void updateCameraVectors();
};
}
#endif // RCAMERA_H
