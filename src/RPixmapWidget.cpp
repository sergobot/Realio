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

//C++
#include <iostream>
//STB
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//Realio
#include "RPixmapWidget.h"

namespace Realio {
RPixmapWidget::RPixmapWidget(
        const int x = 0,
        const int y = 0,
        const int w = 0,
        const int h = 0)
    : RWidget(x,y,w,h)
{
    imgLoaded = false;
}

RPixmapWidget::~RPixmapWidget()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bool RPixmapWidget::loadFile(const char *file)
{
    m_image = stbi_load(file, &img_width, &img_height, &comp, STBI_rgb_alpha);

    if(!m_image)
    {
        std::cerr << "Could not load image '" << file << "' to RPixmapWidget: ";
        std::cerr << stbi_failure_reason() << std::endl;
        return imgLoaded;
    }
    else
        imgLoaded = true;

    return imgLoaded;
}

void RPixmapWidget::show()
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

    float xPos = -1.0f + (float(2 * m_xPos)) / float(m_winWidth);
    float yPos = 1.0f - (float(2 * m_yPos)) / float(m_winHeight);

    float width = float(2 * m_width) / float(m_winWidth);
    float height = float(2 * m_height) / float(m_winHeight);

    GLfloat vertices[] = {
        // Positions              // Texture Coords
        xPos+width,  yPos,        0.0f,   1.0f, 1.0f, // Top Right
        xPos+width,  yPos-height, 0.0f,   1.0f, 0.0f, // Bottom Right
        xPos,        yPos-height, 0.0f,   0.0f, 0.0f, // Bottom Left
        xPos,        yPos,        0.0f,   0.0f, 1.0f  // Top Left
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

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Create texture
    if(comp == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_image);
    else if(comp == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image);

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(m_image);
    glBindTexture(GL_TEXTURE_2D, 0);

    m_shader = new RShader(vShader, fShader);
}

void RPixmapWidget::update()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glUniform1i(glGetUniformLocation(m_shader->getProgram(), "tex"), 0);

    // Activate shader
    m_shader->use();

    // Draw container
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
}
