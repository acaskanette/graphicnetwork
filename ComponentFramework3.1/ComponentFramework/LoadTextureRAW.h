/// Reads Adobe Photoshop .raw format CS2 and on. 
/// There are many "raw" formats out there but this on is by far the 
/// dumbest because it contain no header info about width and height,
/// nor the number of color channels or color depth.  I even makes you
/// guess if its interleaved. My comment in the cpp will expain more. SSF
/// (So here's the prototype.)
#include <GL/glew.h>
//#include <glut.h>
#include <stdio.h>

GLuint loadTextureRAW( const char * filename, int width, int height);