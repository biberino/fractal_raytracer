

#include <iostream>

#include "global.hpp"
#include "ray.hpp"
#include "draw_helper.hpp"
#include "hypercomplex.hpp"
#include "iter.hpp"
#include "functions.hpp"
#include "bmp.hpp"


vector_3d auge(0, 1.5f, 1.0f);
vector_3d fixpunkt(0, 0, 0);
Box box(vector_3d(-2.0f, -2.0f, -2.0f), vector_3d(-2.0f, -2.0f, 2.0f), vector_3d(-2.0f, 2.0f, -2.0f), vector_3d(2.0f, -2.0f, -2.0f));

inline Ray shoot_ray(const Pixel &p, const screen_context &context)
{

    double px = p.x / (double)WIDTH;
    double py = p.y / (double)HEIGHT;

    vector_3d point_on_screen = (context.up_left + (context.l_to_r * px)) + (context.t_to_b * py);
    vector_3d direction = point_on_screen - context.auge;
    direction.normalize();
    return Ray(context.auge, direction);
}

Color calc_pixel(Pixel p, screen_context &context)
{

    Ray r = shoot_ray(p, context);

    double x = 0.0f;
    vector_3d point = r.eval(x);
    while (point.length_squared() < 200.01f)
    {

        if (point.length_squared() <= 2.0f)
        {

            //return Color(255,255,255);
            int value = iter_normal(100, point, 2.0f, mandelbrot_8);
            if (value != -1)
            {
                Color base;
                if (value < 0.1f)
                {
                    base = Color(1, 1, 1);
                }
                else if (value < 0.5f)
                {
                    base = Color(1, 1, 0);
                }
                else if (value < 0.6f)
                {
                    base = Color(1, 0, 0);
                }
                else if (value < 1.8f)
                {
                    base = Color(0, 1, 0);
                }
                else
                {
                    base = Color(0, 0, 1);
                }
                unsigned char scale = (unsigned char)(255.0f - (255.0f * (x / 2.5f)));

                //scale = (unsigned char)(255.0f - (255.0f * ((float)value /4.0f)));
                return Color(base.r * scale, base.g * scale, base.b * scale);
            }
        }

        x += RESOLUTION;
        point = r.eval(x);
    }

    return Color(0, 0, 0);
}

main(int argc, char const *argv[])
{

    std::cout << box.contains(vector_3d(10.0f, 0.5f, 0.5f)) << '\n';

    screen_context context(auge, fixpunkt, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DISTANCE);

    for (size_t i = 0; i < WIDTH; i++)
    {
        for (size_t j = 0; j < HEIGHT; j++)
        {
            bmp_set_pixel(calc_pixel(Pixel(i, j), context), Pixel(i, j));
            //set_pixel(Pixel(i, j), calc_pixel(Pixel(i, j), context), renderer, window);
        }
    }
    bmp_export("test.bmp");

    return 0;
}
