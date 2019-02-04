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
    vec3 intensity_diffuse;
    vec3 intensity_specular;

    vec3 l;
    Light *cur_light;

    for(unsigned int i = 0; i < (world.lights).size(); ++i) {
        cur_light = world.lights.at(i);
	
        //shadow_ray = cur_light->position - intersection_point;
        //shadow_ray_vec = cur_light->position - intersection_point; 
	//intersection = world.Closest_Intersection(shadow_ray);

        //if(intersection.object || intersection.dist <= shadow_ray_vec.magnitude() ) { //equal
            intensity_diffuse += color_diffuse * cur_light->Emitted_Light(intersection_point - cur_light->position) * std::max(dot(normal.normalized(),-(intersection_point - (cur_light->position)).normalized()),0.0);
            
            //view = ray.endpoint - intersection_point;
            //ray_vec = intersection_point - cur_light->position; 
            //reflection = ray_vec.normalized() - 2 * dot(ray_vec.normalized(),normal) * normal;
            l = cur_light->position - intersection_point;

            intensity_specular += color_specular * cur_light->Emitted_Light(intersection_point - cur_light->position) * pow(std::max(dot((intersection_point - ray.endpoint).normalized(),(l - 2 * dot(l,normal)*normal).normalized()),0.0),specular_power);
        //}
    }
    
    color = intensity_ambient + intensity_diffuse + intensity_specular;
    return color;

}
