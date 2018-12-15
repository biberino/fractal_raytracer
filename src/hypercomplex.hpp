#ifndef HYPER_COMPLEX_GUARD
#define HYPER_COMPLEX_GUARD

#include "types.hpp"

vector_3d hyper_mult(const vector_3d& vec1, const vector_3d& vec2);
vector_3d hyper_add(const vector_3d& vec1, const vector_3d& vec2);
vector_3d hyper_pow_constant(const vector_3d& vec1, const int n);
vector_3d hyper_conj(const vector_3d& vec1);

#endif // !HYPER_COMPLEX_GUARD