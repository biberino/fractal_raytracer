
#include "global.hpp"
#include "DrawHelper.hpp"
#include "ray.hpp"

Ray shoot_ray(Pixel p, vector_3d eye, vector_3d look_at)
{
    vector_3d forward = (eye - look_at);
    forward.normalize();

    vector_3d temp(0, 1, 0);
    vector_3d right = temp.cross_prod_with(forward);
    right.normalize();
    vector_3d up = forward.cross_prod_with(right);
    up.normalize();

    std::cout << right.to_string() << '\n';
    //bildschirm bestimmen
    double sw = (double)SCREEN_WIDTH;
    double sh = (double)SCREEN_HEIGHT;
    double dist = (double)SCREEN_DISTANCE;

    vector_3d up_left = (((right * -1) * (sw * 0.5f)) + eye) + (up * (sh * 0.5f));
    vector_3d up_right = (((right) * (sw * 0.5f)) + eye) + (up * (sh * 0.5f));

    vector_3d down_left = (((right * -1) * (sw * 0.5f)) + eye) + (up * (sh * -0.5f));
    vector_3d down_right = (((right) * (sw * 0.5f)) + eye) + (up * (sh * -0.5f));

    up_left = up_left + (forward * -1 * dist);
    up_right = up_right + (forward * -1 * dist);
    down_left = down_left + (forward * -1 * dist);
    down_right = down_right + (forward * -1 * dist);

    std::cout << down_right.to_string() << '\n';

    double px = p.x / (double)WIDTH;
    double py = p.y / (double)HEIGHT;

    vector_3d l_to_r = up_right - up_left;
    vector_3d t_to_b = down_left - up_left;

    vector_3d point_on_screen = (up_left + (l_to_r * px)) + (t_to_b * py);
    vector_3d direction = point_on_screen - eye;
    direction.normalize();
    Ray retVal(eye, direction);
    return retVal;
}

main(int argc, char const *argv[])
{
    Ray r = shoot_ray(Pixel(400, 300), vector_3d(0, 15, 0), vector_3d(0, 0, -100));
    std::cout << r.to_string() << '\n';
    std::cout << r.eval(100.0f).to_string() << '\n';

    return 0;
}
