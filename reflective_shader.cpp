#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{

    vec3 color;
    //percent of reflected light from objects that shows,fully relflective obj=no color
    color = (1-reflectivity)*shader->Shade_Surface(ray,intersection_point,normal,recursion_depth);
    //shade surface->phong shader color
    vec3 d = ray.direction;
    vec3 n = normal;
    vec3 C = d+(-2.0*(dot(d,n)*n));
    Ray rayC(intersection_point,C);

   if(recursion_depth==world.recursion_depth_limit){
       return color;
   }else{
       recursion_depth++;
       return color+(reflectivity*world.Cast_Ray(rayC,recursion_depth));


   }


}
