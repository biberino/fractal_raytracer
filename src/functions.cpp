#include "functions.hpp"

vector_3d mandelbrot(const vector_3d &z, const vector_3d &c)
{
    return hyper_pow_constant(z, 2) + c;
}

vector_3d auge_fraktal(const vector_3d &z, const vector_3d &c)
{
    return hyper_mult(z, hyper_conj(z)) + c;
}

vector_3d mandelbrot_8(const vector_3d &z, const vector_3d &c)
{
    return hyper_pow_constant(z, 8) + c;
}