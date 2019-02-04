#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    double a = dot(ray.direction,ray.direction);
    double b = 2 * dot(ray.direction, ray.endpoint - center);
    double c = dot(ray.endpoint - center, ray.endpoint - center) - radius * radius;
    double determinant = b * b - 4 * a * c;

    if(determinant == 0) {
        double t_positive = (-1 * b) / (2 * a);
        if(t_positive >= small_t) { return {this, t_positive, part}; }
    }
    else if(determinant > 0) {
        double t_positive = ((-1 * b) + sqrt(determinant)) / (2 * a);
        double t_negative = ((-1 * b) - sqrt(determinant)) / (2 * a);
        if(t_positive >= small_t && t_positive < t_negative) { return {this, t_positive, part}; }
	else if(t_negative >= small_t && t_negative < t_positive) { return {this, t_negative, part}; }
    }
    
    return {nullptr, 0, part};
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    normal = ((point - center)/radius); // compute the normal direction
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
