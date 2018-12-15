#ifndef DRAWHELPER_BLA2323
#define DRAWHELPER_BLA2323

#include <string>
#include <cstdlib>
#include <iostream>

#include <SDL2/SDL.h>

#include "global.hpp"
#include "types.hpp"

void set_pixel(const Pixel &p, const Color &c, SDL_Renderer *r, SDL_Window *w);
#endif /* end of include guard: DRAWHELPER_BLA2323 */
