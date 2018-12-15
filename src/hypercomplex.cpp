#include "hypercomplex.hpp"
#include <cmath>

vector_3d hyper_mult(const vector_3d &vec1, const vector_3d &vec2)
{
    double r = std::sqrt(std::pow(vec1.x, 2) + std::pow(vec1.y, 2) + std::pow(vec1.z, 2));
    double theta = std::atan2(std::sqrt(std::pow(vec1.x, 2) + std::pow(vec1.y, 2)), vec1.z);
    double phi = std::atan2(vec1.y, vec1.x);

    double r2 = std::sqrt(std::pow(vec2.x, 2) + std::pow(vec2.y, 2) + std::pow(vec2.z, 2));
    double theta2 = std::atan2(std::sqrt(std::pow(vec2.x, 2) + std::pow(vec2.y, 2)), vec2.z);
    double phi2 = std::atan2(vec2.y, vec2.x);

    double new_x = (r * r2) * std::sin(theta + theta2) * std::cos(phi + phi2);
    double new_y = (r * r2) * std::sin(theta + theta2) * std::sin(phi + phi2);
    double new_z = (r * r2) * std::cos(theta + theta2);

    return vector_3d(new_x, new_y, new_z);
}
vector_3d hyper_add(const vector_3d &vec1, const vector_3d &vec2)
{
    return vec1 + vec2;
}
vector_3d hyper_pow_constant(const vector_3d &vec1, const int n)
{
    double r = std::sqrt(std::pow(vec1.x, 2) + std::pow(vec1.y, 2) + std::pow(vec1.z, 2));
    double theta = std::atan2(std::sqrt(std::pow(vec1.x, 2) + std::pow(vec1.y, 2)), vec1.z);
    double phi = std::atan2(vec1.y, vec1.x);

    double new_x = std::pow(r, n) * std::sin(theta * n) * std::cos(phi * n);
    double new_y = std::pow(r, n) * std::sin(theta * n) * std::sin(phi * n);
    double new_z = std::pow(r, n) * std::cos(theta * n);

    return vector_3d(new_x, new_y, new_z);
}

vector_3d hyper_conj(const vector_3d &vec1)
{
    return vector_3d(vec1.x, -vec1.y, -vec1.z);
}
