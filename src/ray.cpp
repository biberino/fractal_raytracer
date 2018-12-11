#include "ray.hpp"

Ray::Ray()
{
}

Ray::Ray(vector_3d origin, vector_3d direction)
{
    _origin = origin;
    _direction = direction;
}

Ray::~Ray()
{
}

vector_3d Ray::eval(double t)
{
    return _origin + (_direction * t);
}

std::string Ray::to_string()
{
    return std::string("Origin: " + _origin.to_string() + "   Direction: " + _direction.to_string());
}