#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{

    double min_t= std::numeric_limits<double>::max();
    Hit closest_hit={NULL,0,0};

    for(int i=0;i<objects.size();i++){
        //help
       Hit Hitted= objects[i]->Intersection(ray,1);
       if((Hitted.dist<min_t)&&(Hitted.dist>small_t)){
         closest_hit=Hitted;
         min_t=Hitted.dist;
       }
    }
    return closest_hit;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
 // set up the initial view ray here
    Ray ray;
    ray.endpoint=camera.position;
    vec3 dire;
    //normal of z-e
    dire=(camera.World_Position(pixel_index)-ray.endpoint).normalized();
    ray.direction=dire;


    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    vec3 color;
 // determine the color here
    Hit empty={NULL,0,0};
    vec3 no;
    no.fill(0);
    Hit closest_hit= Closest_Intersection(ray);
    if(closest_hit.object!=empty.object){
        //unsure about normal
       vec3 sect= ray.endpoint+(ray.direction*closest_hit.dist);
        color=closest_hit.object->material_shader->Shade_Surface(ray,sect,closest_hit.object->Normal(sect,1),recursion_depth);
    }else{
        //unsure about empty vec3
        color=background_shader->Shade_Surface(ray,no,no,recursion_depth);
    }
    return color;
}

void Render_World::Initialize_Hierarchy()
{
     TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
