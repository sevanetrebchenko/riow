
#ifndef RAYTRACING_GAMEOBJECT_CREATION_H
#define RAYTRACING_GAMEOBJECT_CREATION_H

namespace RT {

    IHittable* MakeSphere(const glm::vec3& translation, float scale, const glm::vec3& rotation, IMaterial* material); // Sphere

}

#endif //RAYTRACING_GAMEOBJECT_CREATION_H
