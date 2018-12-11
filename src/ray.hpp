#ifndef RAY_GUARD
#define RAY_GUARD

#include <string>
#include "types.hpp"


class Ray
{
  public:
    vector_3d _origin;
    vector_3d _direction;

    Ray();
    Ray(vector_3d origin, vector_3d direction);

    ~Ray();


    vector_3d eval(double t);

    std::string to_string();

  private:
};



#endif // !RAY_GUARD
