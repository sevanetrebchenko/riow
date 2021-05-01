
#ifndef RAYTRACER_HITTABLE_FACTORY_H
#define RAYTRACER_HITTABLE_FACTORY_H

#include <pch.h>
#include <raytracer/hittable.h>
#include <raytracer/material.h>

namespace RT {

    IHittable* CreateSphere(const glm::vec3& position, const glm::vec3& rotation, float radius, IMaterial* material);

}

#endif //RAYTRACER_HITTABLE_FACTORY_H
