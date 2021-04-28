
#ifndef RAYTRACING_METALLIC_MATERIAL_H
#define RAYTRACING_METALLIC_MATERIAL_H

#include "glm/glm.hpp"
#include "material.h"
#include "ray.h"
#include "hit_record.h"

namespace RT {

  class MetallicMaterial : public IMaterial {
      public:
          MetallicMaterial(const glm::vec3& color, float fuzziness);
          ~MetallicMaterial() override;

          bool Scatter(const Ray& ray, const HitRecord& hitRecord, glm::vec3& sourceColor, Ray& scatteredRay) const override;

      private:
          glm::vec3 _albedo;
          float _fuzziness;
  };

}

#endif //RAYTRACING_METALLIC_MATERIAL_H
