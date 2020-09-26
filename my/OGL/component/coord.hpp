#include <my/OGL/component/shader.hpp>

#include <GL/gl.h>

namespace my{
namespace OGL::component{
    
    class Coord{
        private:
            GLuint _VBO, _VAO ;
            int _half_extent_coord, _total_point ; 
            float _coord_step ;
            float *_vertices ;
        public :
            Coord(int halfExtentCoord, float coordStep = 1.0f);
            ~Coord();
            void setUpOGL();
            void Draw(const Shader &shader);
    };

}
}