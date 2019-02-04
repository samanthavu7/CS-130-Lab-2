#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color, view, reflection;
    Light *cur_light;
    Ray shadow_ray;
    Hit intersection{};
    vec3 shadow_ray_vec, ray_vec;

    color = color_ambient * world.ambient_color * world.ambient_intensity;

    for(unsigned int i = 0; i < (world.lights).size(); ++i) {
        cur_light = world.lights[i];

        shadow_ray.endpoint = intersection_point;
        shadow_ray.direction = (cur_light->position - intersection_point).normalized();
	
        shadow_ray_vec = cur_light->position - intersection_point; 

	intersection = world.Closest_Intersection(shadow_ray);

        if(intersection.object || intersection.dist <= shadow_ray_vec.magnitude() ) { //equal
            color += color_diffuse * cur_light->Emitted_Light(shadow_ray_vec) * std::max(dot(normal,shadow_ray.direction),0.0);
            
            view = ray.endpoint - intersection_point;
            ray_vec = intersection_point - cur_light->position; 
            reflection = ray_vec.normalized() - 2 * dot(ray_vec.normalized(),normal) * normal;
            
            color += color_specular * cur_light->Emitted_Light(shadow_ray_vec) * pow(std::max(dot(view.normalized(),reflection),0.0),2);
        }
    }
    
    return color;
}
