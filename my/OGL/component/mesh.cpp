#include <my/OGL/component/mesh.hpp>



using namespace my::OGL::component;

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures) :
_vertices(vertices), 
_indices(indices), 
_textures(textures)
{
    setupMesh();
}

Mesh::Mesh(MeshConstructionInfo &meshConstructionInfo):
_vertices(meshConstructionInfo.getVertices()),
_indices(meshConstructionInfo.getIndices()),
_textures(meshConstructionInfo.getTextures())
{
    setupMesh();
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);

    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint), &_indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void Mesh::Draw(Shader &shader)
{
    unsigned int diffuseNr = 1 ;
    unsigned int specularNr = 1 ;
    for (uint i = 0 ; i < _textures.size(); i ++){
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number ;
        std::string name = _textures[i].type ;
        if(name == "texture_diffuse"){
            number = std::to_string(diffuseNr ++ );
        }else if(name == "texture_specular"){
            number = std::to_string(specularNr ++);
        }
        shader.setFloat((name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, _textures[i].id);

    }

    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}