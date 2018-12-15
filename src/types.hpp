#ifndef TYPES_GUARD
#define TYPES_GUARD

#include <cmath>
#include <string>
#include <iostream>

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

    vector_3d(const vector_3d &vec)
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }

    vector_3d operator+(const vector_3d &vec) const
    {
        return vector_3d(x + vec.x, y + vec.y, z + vec.z);
    }

    bool operator==(const vector_3d &vec) const
    {
        std::cout << (*this - vec).to_string() << '\n';
        return ((*this - vec).length_squared() == 0);
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

    double dot_prod_with(const vector_3d &vec) const
    {
        return x * vec.x + y * vec.y + z * vec.z;
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

struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    Color(unsigned char rp, unsigned char gp, unsigned char bp)
    {
        r = rp;
        g = gp;
        b = bp;
    }
    Color() {}
    Color(int hex_value)
    {
        r = ((hex_value >> 16) & 0xFF); // Extract the RR byte
        g = ((hex_value >> 8) & 0xFF);  // Extract the GG byte
        b = ((hex_value)&0xFF);
    }
};

struct screen_context
{
    vector_3d forward;
    vector_3d right;
    vector_3d up;
    vector_3d up_left;
    vector_3d up_right;
    vector_3d down_left;
    vector_3d down_right;
    vector_3d l_to_r;
    vector_3d t_to_b;
    vector_3d auge;

    screen_context(vector_3d eye, vector_3d look_at,
                   double sw, double sh, double dist)
    {
        auge = eye;
        forward = (eye - look_at);
        forward.normalize();

        vector_3d temp(0, 1, 0);

        right = temp.cross_prod_with(forward);
        //if right is arbitary, we decide
        if (right.length_squared() == 0)
        {
            right = vector_3d(1, 0, 0);
        }
        else
        {
            right.normalize();
        }

        up = forward.cross_prod_with(right);
        up.normalize();

        up_left = (((right * -1) * (sw * 0.5f)) + eye) + (up * (sh * 0.5f));
        up_right = (((right) * (sw * 0.5f)) + eye) + (up * (sh * 0.5f));

        down_left = (((right * -1) * (sw * 0.5f)) + eye) + (up * (sh * -0.5f));
        down_right = (((right) * (sw * 0.5f)) + eye) + (up * (sh * -0.5f));

        up_left = up_left + (forward * -1 * dist);
        up_right = up_right + (forward * -1 * dist);
        down_left = down_left + (forward * -1 * dist);
        down_right = down_right + (forward * -1 * dist);

        l_to_r = up_right - up_left;
        t_to_b = down_left - up_left;
    }
};

/**
 * +----+
 * |
 * |   +
 * |
 * +-----
 */

struct Box
{
    vector_3d p1;
    vector_3d p2;
    vector_3d p3;
    vector_3d p4;

    vector_3d u;
    vector_3d v;
    vector_3d w;

    double uP1;
    double vP1;
    double wP1;

    double uP2;
    double vP2;
    double wP2;

    Box(vector_3d pp1, vector_3d pp2, vector_3d pp3, vector_3d pp4)
    {
        p1 = pp1;
        p2 = pp2;
        p3 = pp3;
        p4 = pp4;

        u = p1 - p2;
        v = p1 - p3;
        w = p1 - p4;

        uP1 = u.dot_prod_with(p1);
        uP2 = u.dot_prod_with(p2);

        vP1 = v.dot_prod_with(p1);
        vP2 = v.dot_prod_with(p3);

        wP1 = w.dot_prod_with(p1);
        wP2 = w.dot_prod_with(p4);
    }

    bool contains(vector_3d x)
    {
        if ((u.dot_prod_with(x) <= uP1) && (u.dot_prod_with(x) >= uP2))
        {

            if ((v.dot_prod_with(x) <= vP1) && (v.dot_prod_with(x) >= vP2))
            {

                if ((w.dot_prod_with(x) <= wP1) && w.dot_prod_with(x) >= wP2)
                {
                    return true;
                }
            }
        }

        return false;
    }
};

using func_callback = vector_3d (*)(const vector_3d &, const vector_3d &);

#endif // !TYPES_GUARD