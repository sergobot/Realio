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
#include "R3DObject.h"

namespace Realio {
R3DObject::R3DObject()
{

}

R3DObject::~R3DObject()
{

}

void R3DObject::translate(glm::vec3 vec)
{
    m_modelMatrix = glm::translate(m_modelMatrix, vec);
}

void R3DObject::rotate(glm::vec3 axis, float angle)
{
    m_modelMatrix = glm::rotate(m_modelMatrix, angle, axis);
}

void R3DObject::scale(glm::vec3 ratio)
{
    m_modelMatrix = glm::scale(m_modelMatrix, ratio);
}

void R3DObject::scale(float ratio)
{
    m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(ratio, ratio, ratio));
}

void R3DObject::loadModel(const char *file)
{
    //TODO
    //Load models by ASSIMP
}

glm::mat4 R3DObject::getModelMatrix()
{
    return m_modelMatrix;
}
}
