#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{

    vec3 color;
    //shade surface->phong shader color
    vec3 d = -ray.direction;
    vec3 n = normal;
    vec3 C = (2.0*dot(d,n)*n-(d)).normalized();
    Ray rayC(intersection_point,C);
    //og color
    vec3 SS=shader->Shade_Surface(ray,intersection_point,normal,recursion_depth);
    color=SS;
    //color=Co+reflectivity(Cr-Co);
   if(recursion_depth!=world.recursion_depth_limit){
       recursion_depth++;
       //other color
       vec3 SSR=world.Cast_Ray(rayC,recursion_depth);
       color+=(reflectivity*(SSR-SS));
       return color;
   }else {
       color+=(reflectivity * (-SS));
       return color;
   }


}
