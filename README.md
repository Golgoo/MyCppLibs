# MyCppLibs
Some Reusable Cpp Lybraries
## How to use the code : 
Everything is in the `my` directory
### Some subdir are only header
Just need to pull
### For the other ones :
```
$ cd my/ 
$ cmake .
$ make
```
### Some subdir need other libraries to work
- boost dependency : `cmake . -DBOOST_PATH=<absolute_boost_dir_path>`
  * `logger` subdir
- assimp dependency : `cmake . -DASSIMP_PATH=<absolute_assimp_dir_path>`
  * `OGL` subdir

OGL subdir assume that you have gl / glut and glew install on your machine, it mean that :
- `#include <GL/glew.h>` work 
- `#include <GL/gl.h>` work
- `#include <GL/glut.h>` work
