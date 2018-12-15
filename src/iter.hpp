#ifndef ITER_GUARD
#define ITER_GUARD

#include "types.hpp"
#include "functions.hpp"

int iter_normal(int max_iter, const vector_3d &point, double bailout_squared,
                 func_callback func);

#endif // !ITER_GUARD
