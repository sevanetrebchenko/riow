
set(CORE_SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/src/main.cpp"

        # Raytracer.
        "${PROJECT_SOURCE_DIR}/src/raytracer/application.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/writer.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/ray.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/camera.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/hit_record.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/aabb.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/utility_math.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/material.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/directory.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/intersections.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/sphere.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/hittable.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/hittable_collection.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/hittable_factory.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/texture.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/bvh.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/rotate.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/translate.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/light.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/cube.cpp"
        )

add_executable(RT ${CORE_SOURCE_FILES})

target_include_directories(RT PUBLIC "${PROJECT_SOURCE_DIR}/include/")
target_precompile_headers(RT PRIVATE "${PROJECT_SOURCE_DIR}/include/pch.h")

# DEPENDENCIES
target_link_libraries(RT glm)
target_link_libraries(RT tinyobjloader)
target_link_libraries(RT stb)
