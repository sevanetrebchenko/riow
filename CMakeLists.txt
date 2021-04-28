cmake_minimum_required(VERSION 3.2)

# Project information.
project(Raytracer
        VERSION 1.0
        DESCRIPTION "Course: CS355, Spring2021"
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

# Update git submodules.
find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    message(STATUS "Updating project dependencies to latest versions.")

    option(UPDATE_SUBMODULES "Check submodules during build" ON)
    if(UPDATE_SUBMODULES)
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive # git submodule update --init --recursive
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                RESULT_VARIABLE SUBMODULE_FETCH_RESULT)
        # Check the return value of the above command to make sure it executed properly.
        if(NOT SUBMODULE_FETCH_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${SUBMODULE_FETCH_RESULT}.")
        endif()
    endif()
endif()

# Build third-party dependencies.
add_subdirectory(lib)

# Build souce.
add_subdirectory(src)
