#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    TODO;
    Hit inter;
    vec3 d=ray.direction;
    vec3 e=ray.endpoint;
    vec3 cen=center;
    double a= dot(d,d);
    double b=dot(d*2,e-cen);
    double c=dot(e-cen,e-cen)-radius*radius;
    if((b*b-4*a*c)<0){
        inter.object=this;
        inter.dist=0;
        inter.part=part;
        return inter;
    }
    if((b*b-4*a*c)>0){
        //how to show 2 sol
        inter.object=this;
        //how to show which is closer
        double ans1=(-b+sqrt(b*b-4*a*c))/(2*a);
        double ans2=(-b-sqrt(b*b-4*a*c))/(2*a);
       inter.dist=fmin(ans1,ans2);
        inter.part=part;
        return inter;
    }else{
        inter.object=this;
        inter.part=part;
        double ans1=(-b+sqrt(b*b-4*a*c))/(2*a);
        double ans2=(-b-sqrt(b*b-4*a*c))/(2*a);
        if(isnan(ans1)){
            inter.dist=ans2;
        }else{
            inter.dist=ans1;
        }
        return inter;
    }
  //do i need to show when no sol?

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

