#include "light.h"
#include "object.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    TODO; //determine the color

   for(int i=0; i<world.lights.size();i++){
       //light
       vec3 l=world.lights.at(i)->position-intersection_point;
       //view
       vec3 v=ray.direction;
       //reflect
       vec3 r=((2*dot(v,normal))*normal-v).normalized();
        //R=K, L=intensity
       //emitted light->intensity
       for(int j=0;j<3;j++){
           double LDS=world.lights.at(i)->Emitted_Light(l)[j];
           double firMax=fmax(dot(normal,l.normalized()),0);
           double secMax=fmax(dot(v,r),0);
            //ca
           color[j]+=world.ambient_color[j]*world.ambient_intensity+color_diffuse[j]*LDS*firMax+color_specular[j]*LDS*pow(secMax,specular_power);

       }

   }



    return color;
}
