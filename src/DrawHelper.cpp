#include "DrawHelper.hpp"

DrawHelper::DrawHelper() {}

DrawHelper::~DrawHelper() {}

glutKoordinaten_t DrawHelper::xy_zu_glut_koord(int x, int y)
{
  glutKoordinaten_t glutKoord;

  glutKoord.x = ((float)x / (WIDTH / 2) - 1.0f);
  glutKoord.y = -((float)y / (HEIGHT / 2) - 1.0f);

  //std::cout << glutKoord.x << " " << glutKoord.y << '\n';
  return glutKoord;
}

void DrawHelper::draw_rect_glut(rectange_t rect, const GLfloat *color)
{
  // koordinaten umrechnen
  glutKoordinaten_t begin = xy_zu_glut_koord(rect.x1, rect.y1);
  glutKoordinaten_t end = xy_zu_glut_koord(rect.x2, rect.y2);

  glColor3fv(color);
  glRectf(begin.x, begin.y, end.x, end.y);
}
