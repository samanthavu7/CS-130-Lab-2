#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;

    if(recursion_depth > world.recursion_depth_limit) {
	color = shader->Shade_Surface(ray,intersection_point,normal,recursion_depth); //vec3(0,0,0);
    }
    else {
	color = (1 - reflectivity) * shader->Shade_Surface(ray,intersection_point,normal,recursion_depth);
        vec3 view_ray = ray.endpoint - intersection_point;
        Ray reflected_ray(intersection_point, (2 * dot(view_ray,normal) * normal - view_ray).normalized());
	color += /*(1 - reflectivity) * color*/ + reflectivity * world.Cast_Ray(reflected_ray,recursion_depth+1);
    }    
    return color;
}
