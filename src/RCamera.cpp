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

//Realio
#include "RCamera.h"

namespace Realio {
RCamera* RCamera::global = new RCamera(glm::vec3(1.0f, -1.0f, 3.0f));

RCamera::RCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : m_front(glm::vec3(0.0f, 0.0f, -1.0f))
    ,m_movementSpeed(SPEED)
    ,m_mouseSensitivity(SENSITIVITY)
    ,m_zoom(ZOOM)
{
    m_position = position;
    m_worldUp = up;
    m_yaw = yaw;
    m_pitch = pitch;

    updateCameraVectors();
}

RCamera::~RCamera()
{

}

glm::mat4 RCamera::getViewMatrix()
{
    return glm::lookAt(m_position, this->m_position + this->m_front, this->m_up);
}

void RCamera::reset()
{
    m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    m_movementSpeed = SPEED;
    m_mouseSensitivity = SENSITIVITY;
    m_zoom = ZOOM;
    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_yaw = YAW;
    m_pitch = PITCH;

    updateCameraVectors();
}

void RCamera::move(RCameraMoveDirection direction, float deltaTime)
{
    float velocity = this->m_movementSpeed * deltaTime;

    if (direction == FORWARD)
        m_position += this->m_front * velocity;
    if (direction == BACKWARD)
        m_position -= this->m_front * velocity;
    if (direction == LEFT)
        m_position -= this->m_right * velocity;
    if (direction == RIGHT)
        m_position += this->m_right * velocity;
}

void RCamera::zoom(float ratio)
{
    m_zoom *= ratio;
}

float RCamera::getZoomRatio()
{
    return m_zoom;
}

void RCamera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw   += xoffset;
    m_pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Eular angles
    updateCameraVectors();
}

void RCamera::setMovementSpeed(float speed)
{
    m_movementSpeed = speed;
}

float RCamera::getMovementSpeed()
{
    return m_movementSpeed;
}

void RCamera::updateCameraVectors()
{
    // Calculate the new front vector
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    // Also re-calculate the right and up vector
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}
}
