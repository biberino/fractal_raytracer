#ifndef BMP_GUARD
#define BMP_GUARD


#include <string>
#include "global.hpp"
#include "types.hpp"


void bmp_set_pixel(const Color& c, const Pixel& p);
void bmp_export(const std::string filename);

#endif // !BMP_GUARD