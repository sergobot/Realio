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

// Realio
#include "RShader.h"
// ASSIMP
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// SDL2
#include <SDL2/SDL.h>

namespace Realio {
class R3DObject
{
public:
    R3DObject();
    virtual ~R3DObject();

    /**
     * @brief moves the object.
     * @param 3D vector from GLM.
     * @return void.
     */
    void translate(const glm::vec3 vec);

    /**
     * @brief rotates the object.
     * @param rotate angle in float.
     * @return void.
     */
    void rotate(const glm::vec3 axis, const float angle);

    /**
     * @brief scales the object.
     * @param scaling ratio for each axis in 3D vector from GLM.
     * @return void.
     */
    void scale(const glm::vec3 ratio);

    /**
     * @brief scales the object.
     * @param one scaling ratio in float for all axes.
     * @return void.
     */
    void scale(const float ratio);

    /**
     * @brief draws the object to scene.
     * @param void.
     * @return void.
     */
    void draw();
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
    enum R3DObjectTextureType {
        R3DOBJECT_DIFFUSE_TEXTURE,
        R3DOBJECT_SPECULAR_TEXTURE,
        R3DOBJECT_NORMAL_TEXTURE
    };

    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoord;
        glm::vec3 tangent;
        glm::vec3 bitangent;
    };

    struct Texture {
        GLuint id = 0;  // OpenGL texture ID
        R3DObjectTextureType type = R3DOBJECT_DIFFUSE_TEXTURE;
        std::string path = ""; // Path to texture's image
        std::string name = ""; // Texture's variable name in fragment shader
    };
    std::vector<Texture*> m_textures;

    struct Mesh {
        GLuint VAO = 0, VBO = 0, EBO = 0;
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture*> textures;

        RShader *shader = nullptr;
    };
    std::vector<Mesh> m_meshes;

    std::string m_directory;
    glm::mat4 m_modelMatrix;
    RShader *m_shader;

    /**
     * @brief creates shaders. Call it only once!
     * @param void.
     * @return void.
     */
    RShader* createShaders();

private:
    /**
     * @brief recursively processes all child nodes of the given one.
     * @param a node, nedeed to process and scene, containing the node.
     * @return void.
     */
    void processNode(const aiNode *node, const aiScene *scene);

    /**
     * @brief fills this->m_meshes with data the mesh contains.
     * @param a mesh, nedeed to process and scene, containing the mesh.
     * @return Mesh struct.
     */
    Mesh processMesh(const aiMesh *mesh, const aiScene *scene);

    /**
     * @brief sets the mesh's VAO/VBO/EBO.
     * @param pointer to a mesh, needed to setup.
     * @return void.
     */
    void setupMesh(Mesh *mesh);

    /**
     * @brief loads all needed textures for an aiMaterial object.
     * @param aiMaterial object, texture type.
     * @return void.
     */
    std::vector<Texture*> loadMaterialTextures(const aiMaterial *material, const R3DObjectTextureType type);
};
}

#endif // R3DOBJECT_H
