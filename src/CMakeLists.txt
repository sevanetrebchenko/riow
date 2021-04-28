
set(CORE_SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/src/main.cpp"

        # Raytracer.
        "${PROJECT_SOURCE_DIR}/src/raytracer/aabb.cpp"

        # Writers.
        "${PROJECT_SOURCE_DIR}/src/raytracer/writers/image_writer.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/writers/ppm_writer.cpp"
        "${PROJECT_SOURCE_DIR}/src/raytracer/writers/jpg_writer.cpp"
        )

add_executable(RT ${CORE_SOURCE_FILES})

target_include_directories(RT PUBLIC "${PROJECT_SOURCE_DIR}/include/")
target_precompile_headers(RT PRIVATE "${PROJECT_SOURCE_DIR}/include/pch.h")

# DEPENDENCIES
target_link_libraries(RT glm)
target_link_libraries(RT tinyobjloader)
target_link_libraries(RT stb)
