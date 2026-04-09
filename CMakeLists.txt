cmake_minimum_required(VERSION 3.16)

project(MassSpringDamper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sim src/main.cpp src/plant.cpp src/export_data.cpp)
target_include_directories(sim PRIVATE include)
target_compile_definitions(sim PRIVATE PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")

set(PYTHON_EXECUTABLE "${CMAKE_SOURCE_DIR}/.venv/bin/python")

add_custom_target(run_and_plot
    COMMAND $<TARGET_FILE:sim>
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/plot_results.py
    WORKING_DIRECTORY ${CMAKE_BIN_DIR}
    DEPENDS sim
)