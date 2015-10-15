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
#include "RCamera.h"
#include <iostream>

namespace Realio {
R3DObject::R3DObject()
{
    m_modelMatrix = glm::mat4();
    m_colored = false;
    m_textured = false;

    m_shader = nullptr;
    createShaders();
}

R3DObject::~R3DObject()
{
    if(m_shader)
    {
        m_shader->deleteProgram();
        delete m_shader;
    }
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

    if(!m_colored && !m_textured)
        m_colored = true;
    createShaders();
}

glm::mat4 R3DObject::getModelMatrix()
{
    return m_modelMatrix;
}

void R3DObject::draw()
{
    //TODO
    //Make it able to draw 3D objects
}

void R3DObject::createShaders()
{
    if(m_shader != nullptr)
    {
        m_shader->deleteProgram();
        delete m_shader;
    }

    //Object colored and textured
    if(m_colored && m_textured)
    {
        const char vShader[] = {
            "#version 330 core\n"
            "layout (location = 0) in vec3 position;"
            "layout (location = 1) in vec2 texCoord;"
            "out vec2 TexCoord;"
            "uniform mat4 model;"
            "uniform mat4 view;"
            "uniform mat4 projection;"
            "void main() {"
            "    gl_Position = projection * view * model * vec4(position, 1.0f);"
            "    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);"
            "}"
        };

        const char fShader[] = {
            "#version 330 core\n"
            "in vec2 TextCoord;"
            "out vec4 color;"
            "uniform sampler2D Texture;"
            "uniform vec4 Color;"
            "void main() {"
            "    color = texture(Texture, TexCoord) * Color;"
            "}"
        };

        m_shader = new RShader(vShader, fShader);
    }
    //Object textured, but not colored
    else if(m_textured)
    {
        const char vShader[] = {
            "#version 330 core\n"
            "layout (location = 0) in vec3 position;"
            "layout (location = 1) in vec2 texCoord;"
            "out vec2 TexCoord;"
            "uniform mat4 model;"
            "uniform mat4 view;"
            "uniform mat4 projection;"
            "void main() {"
            "    gl_Position = projection * view * model * vec4(position, 1.0f);"
            "    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);"
            "}"
        };

        const char fShader[] = {
            "#version 330 core\n"
            "in vec2 TexCoord;"
            "out vec4 color;"
            "uniform sampler2D Texture;"
            "void main() {"
            "    color = texture(Texture, TexCoord).rgba;"
            "}"
        };

        m_shader = new RShader(vShader, fShader);
    }
    //Object colored, but not textured
    else if(m_colored)
    {
        const char vShader[] = {
            "#version 330 core\n"
            "layout (location = 0) in vec3 position;"
            "out vec2 TexCoord;"
            "uniform mat4 model;"
            "uniform mat4 view;"
            "uniform mat4 projection;"
            "void main() {"
            "    gl_Position = projection * view * model * vec4(position, 1.0f);"
            "}"
        };

        const char fShader[] = {
            "#version 330 core\n"
            "out vec4 color;"
            "uniform vec4 Color;"
            "void main() {"
            "    color = Color;"
            "}"
        };

        m_shader = new RShader(vShader, fShader);
    }
    else
    {
        const char vShader[] = {
            "#version 330 core\n"
            "layout (location = 0) in vec3 position;"
            "layout (location = 1) in vec2 texCoord;"
            "out vec2 TexCoord;"
            "void main() {"
            "    gl_Position = vec4(position, 1.0f);"
            "    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);"
            "}"
        };
        const char fShader[] = {
            "#version 330 core\n"
            "in vec2 TexCoord;"
            "out vec4 color;"
            "uniform sampler2D tex;"
            "void main() {"
            "    color = texture(tex, TexCoord).rgba;"
            "}"
        };

        m_shader = new RShader(vShader, fShader);
    }
}
}
