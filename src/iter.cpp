#include "iter.hpp"

int iter_normal(int max_iter, const vector_3d &point, double bailout_squared,
                 func_callback func)
{
    vector_3d c(point);
    vector_3d z(0, 0, 0);

    for (size_t i = 0; i < max_iter; i++)
    {
        z = func(z, c);

        if (z.length_squared() > bailout_squared)
        {
            return -1;
        }
    }

    return z.length_squared();
}