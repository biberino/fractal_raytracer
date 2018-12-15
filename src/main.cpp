

#include <SDL2/SDL.h>
#include <iostream>

#include "global.hpp"
#include "ray.hpp"
#include "draw_helper.hpp"

// TODO: finde den bug
vector_3d auge(0.0f, -3.0f, 0.0f);
vector_3d fixpunkt(0, 0, 0.001f);
Box box(vector_3d(0, 0, 0), vector_3d(0, 0, 1.0f), vector_3d(0, 1.0f, 0), vector_3d(1.0f, 0, 0));

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
    while (point.length_squared() < 50.2f)
    {
        
        if (point.length_squared() <= 1.0f)
        {
            unsigned char c = 255.0f - ((x / 3.0f) * 255.0f);
            return Color(c, c, c);
        }
        
        if (box.contains(point))
        {
            unsigned char c = 255.0f - ((x / 3.0f) * 255.0f);
            return Color(c, c, c);
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

    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    for (size_t i = 0; i < WIDTH; i++)
    {
        for (size_t j = 0; j < HEIGHT; j++)
        {
            set_pixel(Pixel(i, j), calc_pixel(Pixel(i, j), context), renderer, window);
        }
    }
    SDL_RenderPresent(renderer);
    while (1)
    {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
