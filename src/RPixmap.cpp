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

// Realio
#include "RPixmap.h"
#include "RCamera.h"
// C++
#include <iostream>
// STB
#include "stb/stb_image.h"

namespace Realio {
RPixmap::RPixmap(
        const int x = 0,
        const int y = 0,
        const int w = 0,
        const int h = 0)
    : RWidget(x,y,w,h)
{
    imgLoaded = false;
}

RPixmap::RPixmap(
        const int x = 0,
        const int y = 0)
    : RWidget(x,y,0,0)
{
    imgLoaded = false;
}

RPixmap::RPixmap()
    : RWidget(0,0,0,0)
{
    imgLoaded = false;
}

/*virtual*/ RPixmap::~RPixmap()
{
    if(imgLoaded)
    {
        stbi_image_free(m_image);
        glDeleteTextures(1, &m_texture);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bool RPixmap::loadFile(const char *file)
{
    if(!imgLoaded)
        glGenTextures(1, &m_texture);

    imgLoaded = false;
    m_image = stbi_load(file, &img_width, &img_height, &comp, STBI_rgb_alpha);

    if(!m_image)
    {
        std::cerr << "Could not load image '" << file << "' to RPixmap: ";
        std::cerr << stbi_failure_reason() << std::endl;
        glDeleteTextures(1, &m_texture); // Delete texture
        return imgLoaded;
    }
    else
        imgLoaded = true;

    if(!m_height && !m_width)
    {
        m_height = img_height;
        m_width = img_width;
    }

    glBindTexture(GL_TEXTURE_2D, m_texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Create texture
    glTexImage2D(GL_TEXTURE_2D, 0, comp == 3 ? GL_RGB : GL_RGBA, m_width, m_height,
                 0, comp == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, m_image);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    return imgLoaded;
}

/*virtual*/ void RPixmap::show()
{
    if(!imgLoaded)
        return;
    // Update vertex shader
    m_shader->addInputVariable("texCoord", RSHADER_VEC2_VARIABLE, RSHADER_VERTEX_SHADER, true);
    m_shader->addOutputVariable("TexCoord", RSHADER_VEC2_VARIABLE, RSHADER_VERTEX_SHADER, false);
    m_shader->addAction("TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);\n", RSHADER_VERTEX_SHADER);
    // Update fragment shader
    m_shader->addInputVariable("TexCoord", RSHADER_VEC2_VARIABLE, RSHADER_FRAGMENT_SHADER, false);
    m_shader->addUniform("Texture", RSHADER_SAMPLER2D_VARIABLE, RSHADER_FRAGMENT_SHADER);
    m_shader->addAction("color = texture(Texture, TexCoord).rgba;\n", RSHADER_FRAGMENT_SHADER);

    initializeVertices();
    // Compile those shaders
    m_shader->compileShaders();

    update();
}

/*virtual*/ void RPixmap::update()
{
    if(!imgLoaded)
        return;

    // Activate shader
    m_shader->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glUniform1i(glGetUniformLocation(m_shader->getProgram(), "Texture"), 0);

    glm::mat4 view;
    glm::mat4 projection;

    // Pass the matrices to the shader
    glUniformMatrix4fv(glGetUniformLocation(m_shader->getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(m_modelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(m_shader->getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(m_shader->getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // Draw container
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void RPixmap::initializeVertices()
{
    if(!imgLoaded)
        return;

    float width = float(2 * m_width) / float(m_winWidth);
    float height = float(2 * m_height) / float(m_winHeight);

    GLfloat vertices[] = {
        // Positions                      // Texture Coords
        -1.0f+width,  1.0f,        0.0f,   1.0f, 1.0f, // Top Right
        -1.0f+width,  1.0f-height, 0.0f,   1.0f, 0.0f, // Bottom Right
        -1.0f,        1.0f-height, 0.0f,   0.0f, 0.0f, // Bottom Left
        -1.0f,        1.0f,        0.0f,   0.0f, 1.0f  // Top Left
    };

    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Texture attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO
}

void RPixmap::fitByImage()
{
    if(!imgLoaded)
        return;

    m_width = img_width;
    m_height = img_height;
}
}
