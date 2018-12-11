#ifndef DRAWHELPER_BLA2323
#define DRAWHELPER_BLA2323

#include <GL/glut.h> // GLUT
#include <GL/glu.h>  // GLU
#include <GL/gl.h>   // OpenGL
#include <string>
#include <cstdlib>
#include <iostream>

#include "global.hpp"

struct glutKoordinaten_t
{
  GLfloat x;
  GLfloat y;
};

struct rectange_t
{
  int x1;
  int x2;
  int y1;
  int y2;
};

class DrawHelper
{
private:
  glutKoordinaten_t xy_zu_glut_koord(int x,
                                     int y);

public:
  DrawHelper();
  virtual ~DrawHelper();

  void draw_rect_glut(rectange_t rect,
                      const GLfloat *color);
};

#endif /* end of include guard: DRAWHELPER_BLA2323 */
