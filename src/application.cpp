#include "application.h"

#include <raylib.h>

Application::Application(int width, int height, const char* title)
    : scene_(createScene())
    , camera_({ 180.0F, 180.0F }, 0.0F, 60.0F * DEG2RAD)
    , raycaster_(320, 900.0F)
{
    InitWindow(width, height, title);
    SetTargetFPS(60);
}

Application::~Application()
{
    CloseWindow();
}

void Application::run()
{
    while (!WindowShouldClose())
    {
        update(GetFrameTime());

        BeginDrawing();
        draw();
        EndDrawing();
    }
}

void Application::update(float delta_time)
{
    camera_.update(delta_time);

    if (IsKeyPressed(KEY_TAB))
    {
        show_top_down_ = !show_top_down_;
    }
}

void Application::draw() const
{
    const std::vector<geom::RayHit> hits = raycaster_.cast(camera_, scene_);

    if (show_top_down_)
    {
        renderer_.drawTopDown(scene_, camera_, hits);
        return;
    }

    renderer_.drawFirstPerson(scene_, camera_, hits);
}

Scene Application::createScene() const
{
    Scene scene;

    scene.addWall({ { 80.0F, 80.0F }, { 1180.0F, 80.0F }, LIGHTGRAY });
    scene.addWall({ { 1180.0F, 80.0F }, { 1180.0F, 640.0F }, LIGHTGRAY });
    scene.addWall({ { 1180.0F, 640.0F }, { 80.0F, 640.0F }, LIGHTGRAY });
    scene.addWall({ { 80.0F, 640.0F }, { 80.0F, 80.0F }, LIGHTGRAY });
    scene.addWall({ { 280.0F, 170.0F }, { 760.0F, 250.0F }, GREEN });
    scene.addWall({ { 780.0F, 520.0F }, { 1080.0F, 360.0F }, RED });
    scene.addWall({ { 390.0F, 500.0F }, { 520.0F, 310.0F }, PURPLE });

    return scene;
}
