if(DEFINED ASSIMP_PATH)
include_directories(${ASSIMP_PATH}/include)
link_directories(${ASSIMP_PATH}/lib)

FILE(GLOB SOURCES component/*.cpp)

add_library(myogl SHARED
    ${SOURCES}
)
target_link_libraries(
    myogl
    glut
    GLU
    GL
    GLEW
    assimp
)
set_target_properties(myogl PROPERTIES VERSION ${PROJECT_VERSION})
else(DEFINED ASSIMP_PATH)
    message(WARNING 
"ASSIMP is not set and is need to compile OGL libs
You can specify assimp path with this run of cmake :
-DASSIMP_PATH=<absolute_assimp_directory_path>")
endif(DEFINED ASSIMP_PATH)