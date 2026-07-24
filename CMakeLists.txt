cmake_minimum_required(VERSION 3.14)
project(raycast VERSION 1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    src/application.cpp
    src/camera.cpp
    src/geometry.cpp
    src/main.cpp
    src/raycaster.cpp
    src/renderer.cpp
    src/scene.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/raylibdll.lib
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/raylib.dll
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
