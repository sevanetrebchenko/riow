
set(CORE_SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/src/main.cpp"

        # Raytracer.
        "${PROJECT_SOURCE_DIR}/src/raytracer/application.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/writer.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/ray.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/camera.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/hit_record.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/intersectable.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/intersectable_collection.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/aabb.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/utility_math.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/transform.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/material.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/directory.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/object_loader.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/mesh.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/model.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/intersections.cpp"
        )

add_executable(RT ${CORE_SOURCE_FILES})

target_include_directories(RT PUBLIC "${PROJECT_SOURCE_DIR}/include/")
target_precompile_headers(RT PRIVATE "${PROJECT_SOURCE_DIR}/include/pch.h")

# DEPENDENCIES
target_link_libraries(RT glm)
target_link_libraries(RT tinyobjloader)
target_link_libraries(RT stb)
