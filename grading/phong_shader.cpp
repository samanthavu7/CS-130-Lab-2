#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    vec3 intensity_ambient = color_ambient * world.ambient_color * world.ambient_intensity;
    vec3 intensity_diffuse, intensity_specular;

    vec3 shadow_ray, ray_vec, reflected_ray;
    Ray shadow_ray_ray;
    Light *cur_light;
    Hit intersection{};

    for(unsigned int i = 0; i < world.lights.size(); i++) {
        cur_light = world.lights.at(i);
	
        shadow_ray = cur_light->position - intersection_point; 
	shadow_ray_ray.endpoint = intersection_point;
        shadow_ray_ray.direction = (cur_light->position - intersection_point).normalized();
        ray_vec = intersection_point - ray.endpoint;
        reflected_ray = shadow_ray - 2 * dot(shadow_ray, normal) * normal;
  
        intersection = world.Closest_Intersection(shadow_ray_ray);

        if(intersection.object || intersection.dist < shadow_ray.magnitude() ) { //equal
            intensity_diffuse += color_diffuse * cur_light->Emitted_Light(shadow_ray) * std::max(dot(normal,shadow_ray.normalized()),0.0);
            
            intensity_specular += color_specular * cur_light->Emitted_Light(shadow_ray) * pow(std::max(dot(ray_vec.normalized(),reflected_ray.normalized()),0.0), specular_power);
        }
    }
    
    color = intensity_ambient + intensity_diffuse + intensity_specular;
    return color;

}
