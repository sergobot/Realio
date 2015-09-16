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

#ifndef R3DOBJECT_H
#define R3DOBJECT_H

//SDL2
#include <SDL2/SDL.h>
//GLEW
#include <GL/glew.h>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Realio {
class R3DObject
{
public:
    R3DObject();
    ~R3DObject();

    /**
     * @brief moves the object.
     * @param 3D vector from GLM.
     * @return void.
     */
    void translate(glm::vec3 vec);

    /**
     * @brief rotetes the object.
     * @param rotate angle in float.
     * @return void.
     */
    void rotate(glm::vec3 axis, float angle);

    /**
     * @brief scales the object.
     * @param scaling ratio for each axis in 3D vector from GLM.
     * @return void.
     */
    void scale(glm::vec3 ratio);

    /**
     * @brief scales the object.
     * @param one scaling ratio in float for all axes.
     * @return void.
     */
    void scale(float ratio);

    /**
     * @brief loads the object.
     * @param 3D vector from GLM.
     * @return void.
     */
    void loadModel(const char* file);

    /**
     * @brief returns current model matrix.
     * @param void.
     * @return 4x4 matrix from GLM.
     */
    glm::mat4 getModelMatrix();

protected:
    glm::mat4 m_modelMatrix;
};
}

#endif // R3DOBJECT_H
