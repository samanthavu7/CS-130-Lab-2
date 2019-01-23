#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    double a = dot(ray.direction,ray.direction);
    double b = 2 * dot(ray.direction, ray.endpoint - center);
    double c = dot(ray.endpoint - center, ray.endpoint - center) - radius * radius;
    double t = 0;
    if(b * b - 4 * a * c == 0) {
        t = (-1 * b) / (2 * a);
    }
    else if((b * b - 4 * a * c) > 0) {
        double t_positive = ((-1 * b) + (b * b - 4 * a * c)) / (2 * a);
        double t_negative = ((-1 * b) - (b * b - 4 * a * c)) / (2 * a);
        if(t_positive >= t_negative) { t = t_positive; }
	else { t = t_negative; }
    }
    if(t >= small_t) { return {this, t, part}; }
    return {0,0,0};
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    TODO; // compute the normal direction
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
