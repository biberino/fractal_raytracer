#ifndef TYPES_GUARD
#define TYPES_GUARD

#include <cmath>
#include <string>

struct vector_3d
{
    double x;
    double y;
    double z;

    vector_3d()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    vector_3d(double xp, double yp, double zp)
    {
        x = xp;
        y = yp;
        z = zp;
    }

    vector_3d operator+(const vector_3d &vec) const
    {
        return vector_3d(x + vec.x, y + vec.y, z + vec.z);
    }

    vector_3d operator-(const vector_3d &vec) const
    {
        return vector_3d(x - vec.x, y - vec.y, z - vec.z);
    }

    vector_3d &operator=(const vector_3d &vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        return *this;
    }

    vector_3d operator*(const double &d) const
    {
        return vector_3d(x * d, y * d, z * d);
    }

    double length()
    {
        return std::sqrt((x * x) + (y * y) + (z * z));
    }

    double length_squared()
    {
        return (x * x) + (y * y) + (z * z);
    }

    void normalize()
    {
        double l = length();
        x = x / l;
        y = y / l;
        z = z / l;
    }

    vector_3d cross_prod_with(const vector_3d &vec) const
    {
        return vector_3d((y * vec.z - z * vec.y), z * vec.x - x * vec.z, x * vec.y - y * vec.x);
    }

    std::string to_string()
    {
        return std::string("(" + std::to_string(x) + "|" + std::to_string(y) + "|" + std::to_string(z) + ")");
    }
};

struct Pixel
{
    int x;
    int y;
    Pixel(int px, int py)
    {
        x = px;
        y = py;
    }
};

#endif // !TYPES_GUARD