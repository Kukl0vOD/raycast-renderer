#pragma once

#include "camera.h"
#include "raycaster.h"
#include "renderer.h"
#include "scene.h"

class Application
{
public:
    Application(int width, int height, const char* title);
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void run();

private:
    void update(float delta_time);
    void draw() const;
    Scene createScene() const;

    Scene scene_;
    ViewCamera camera_;
    Raycaster raycaster_;
    Renderer renderer_;
    bool show_top_down_{};
};
