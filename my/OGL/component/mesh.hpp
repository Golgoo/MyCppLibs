#pragma once

#include <glm/glm.hpp>

#include <string>

#include <vector>

#include <my/OGL/component/shader.hpp>

#include <GL/gl.h>

#include <numeric>

namespace my{
namespace OGL::component{

    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };

    struct Texture {
        GLuint id ;
        std::string type ;
        std::string path ;
    };

    class MeshConstructionInfo{
        private:
            std::vector<Vertex> _vertices = {};
            std::vector<GLuint> _indices = {};
            std::vector<Texture> _textures = {};
        public:
            void setVertices(std::vector<Vertex> vertices){_vertices = vertices ; }
            void setIndices(std::vector<GLuint> indices){_indices = indices ;}
            void setTexture(std::vector<Texture> textures){_textures = textures ;}
            std::vector<Vertex> getVertices(){return _vertices ;}
            std::vector<GLuint> getIndices(){
                if(_indices.empty() && !_vertices.empty()){
                    _indices.resize(_vertices.size());
                    std::iota(std::begin(_indices), std::end(_indices), 0);
                }
                return _indices ;
            }
            std::vector<Texture> getTextures(){return _textures;}
            
    };

    class Mesh{
        public:

            Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices = {}, std::vector<Texture> textures = {});
            Mesh(MeshConstructionInfo &meshConstructionInfo);
            void Draw(Shader &shader);

        private:
            std::vector<Vertex> _vertices ;
            std::vector<GLuint> _indices ;
            std::vector<Texture> _textures ;
            GLuint _VAO, _VBO, _EBO ;

            void setupMesh();
    };

    
    
}
}
