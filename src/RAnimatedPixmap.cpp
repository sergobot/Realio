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
#include "RAnimatedPixmap.h"
//C++
#include <iostream>
//STB
#include "stb/stb_image.h"

namespace Realio {
RAnimatedPixmap::RAnimatedPixmap(
        const int x = 0,
        const int y = 0,
        const int w = 0,
        const int h = 0)
    : RPixmap(x,y,w,h)
{
    currentFrame = 0;
}

RAnimatedPixmap::RAnimatedPixmap(
        const int x = 0,
        const int y = 0)
    : RPixmap(x,y)
{
    currentFrame = 0;
}

RAnimatedPixmap::RAnimatedPixmap()
    : RPixmap()
{
    currentFrame = 0;
}

RAnimatedPixmap::~RAnimatedPixmap()
{
    for(unsigned i = 0; i < m_images.size(); ++i)
    {
        stbi_image_free(m_images[i]->image);
        delete m_images.at(i);
    }

    imgLoaded = false;
}

bool RAnimatedPixmap::loadFile(const char *file)
{
    Image *img = new Image;
    img->image = stbi_load(file, &img->w, &img->h, &img->comp, STBI_rgb_alpha);

    if(!img->image)
    {
        std::cerr << "Could not load image '" << file << "' to RAnimatedPixmap: ";
        std::cerr << stbi_failure_reason() << std::endl;
        delete img;
        return imgLoaded;
    }
    else
        imgLoaded = true;

    img->index = m_images.size();

    m_images.push_back(img);

    m_textured = true;
    m_colored = false;

    return imgLoaded;
}

/*virtual*/ void RAnimatedPixmap::show()
{
    if(!imgLoaded)
        return;

    Image *img = m_images[currentFrame];

    if(!m_height && !m_width)
    {
        m_height = img->h;
        m_width = img->w;
    }

    //Update vertex shader
    m_shader->addInputVariable("texCoord", RSHADER_VEC2_VARIABLE, RSHADER_VERTEX_SHADER, true);
    m_shader->addOutputVariable("TexCoord", RSHADER_VEC2_VARIABLE, RSHADER_VERTEX_SHADER, false);
    m_shader->addAction("TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);\n", RSHADER_VERTEX_SHADER);
    //Update fragment shader
    m_shader->addInputVariable("TexCoord", RSHADER_VEC2_VARIABLE, RSHADER_FRAGMENT_SHADER, false);
    m_shader->addUniform("Texture", RSHADER_SAMPLER2D_VARIABLE, RSHADER_FRAGMENT_SHADER);
    m_shader->addAction("color = texture(Texture, TexCoord).rgba;\n", RSHADER_FRAGMENT_SHADER);

    initializeVertices();
    //Compile those shaders
    m_shader->compileShaders();

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Create texture
    if(img->comp == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->image);
    else if(img->comp == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->image);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    update();
}

void RAnimatedPixmap::fitByImage()
{
    if(!imgLoaded)
        return;

    Image *img = m_images[currentFrame];

    m_width = img->w;
    m_height = img->h;
}

void RAnimatedPixmap::nextFrame()
{
    if(currentFrame == m_images.size() - 1)
        currentFrame = 0;
    else
        currentFrame++;

    Image *img = m_images[currentFrame];

    m_width = img->w;
    m_height = img->h;

    show();
}
}
