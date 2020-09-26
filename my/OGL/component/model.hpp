#pragma once

#include <vector>
#include <string>


#include <my/OGL/component/shader.hpp>
#include <my/OGL/component/mesh.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace my{
namespace OGL::component{

    class Model 
    {
        public:
            Model(std::string path)
            {
                loadModel(path);
            }
            void Draw(Shader &shader);	
            std::vector<Mesh> _meshes;
            std::vector<Texture> _textures_loaded ;
        private:
            // model data
            std::string _directory;

            void loadModel(std::string path);
            void processNode(aiNode *node, const aiScene *scene);
            Mesh processMesh(aiMesh *mesh, const aiScene *scene);
            std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                                std::string typeName);

        private:
            int totalTextures = 0 ;
            int expectedTextures = 0 ;
            int totalMesh = 0 ;
            int totalVertices = 0 ; 
            int totalNode = 0 ;
    };

}
}
