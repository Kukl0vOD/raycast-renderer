#include "renderer.h"

#include <algorithm>
#include <cmath>
#include <raylib.h>

namespace
{
Color shade(Color color, float factor)
{
    factor = std::clamp(factor, 0.15F, 1.0F);

    return
    {
        static_cast<unsigned char>(static_cast<float>(color.r) * factor),
        static_cast<unsigned char>(static_cast<float>(color.g) * factor),
        static_cast<unsigned char>(static_cast<float>(color.b) * factor),
        color.a,
    };
}
}

void Renderer::drawTopDown(const Scene& scene, const ViewCamera& camera, const std::vector<geom::RayHit>& hits) const
{
    ClearBackground({ 18, 18, 20, 255 });

    for (const Wall& wall : scene.getWalls())
    {
        DrawLineEx(wall.start, wall.end, 4.0F, wall.color);
    }

    for (const geom::RayHit& hit : hits)
    {
        const Color ray_color = hit.hit ? Color{ 255, 214, 102, 120 } : Color{ 120, 120, 130, 70 };
        DrawLineEx(camera.getPosition(), hit.point, 1.0F, ray_color);

        if (hit.hit)
        {
            DrawCircleV(hit.point, 3.0F, ORANGE);
        }
    }

    DrawCircleV(camera.getPosition(), 7.0F, SKYBLUE);
    DrawLineEx(camera.getPosition(), camera.getPosition() + geom::fromAngle(camera.getAngle()) * 28.0F, 3.0F, BLUE);

    DrawText("W/S move, <-/-> turn, A/D strafe, Up/Down look, Shift faster, Tab view", 16, 16, 20, RAYWHITE);
}

void Renderer::drawFirstPerson(const Scene& scene, const ViewCamera& camera, const std::vector<geom::RayHit>& hits) const
{
    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();
    const float projection_plane_distance = static_cast<float>(screen_width) * 0.5F / std::tan(camera.getFov() * 0.5F);
    const float column_width = static_cast<float>(screen_width) / static_cast<float>(hits.size());
    const float wall_scale = 90.0F;
    const float pitch_offset = std::tan(camera.getPitch()) * projection_plane_distance;
    const float horizon_y = static_cast<float>(screen_height) * 0.5F + pitch_offset;
    const int horizon_line = std::clamp(static_cast<int>(horizon_y), 0, screen_height);

    ClearBackground(BLACK);
    DrawRectangle(0, 0, screen_width, horizon_line, { 38, 42, 49, 255 });
    DrawRectangle(0, horizon_line, screen_width, screen_height - horizon_line, { 24, 24, 25, 255 });

    for (int i = 0; i < static_cast<int>(hits.size()); ++i)
    {
        const geom::RayHit& hit = hits[i];

        if (!hit.hit)
        {
            continue;
        }

        const Wall& wall = scene.getWalls()[hit.wall_index];
        const float corrected_distance = hit.distance * std::cos(hit.ray_angle - camera.getAngle());
        const float wall_height = wall_scale * projection_plane_distance / std::max(corrected_distance, 1.0F);
        const float x = static_cast<float>(i) * column_width;
        const float y = horizon_y - wall_height * 0.5F;
        const float light = 1.0F - std::clamp(corrected_distance / 800.0F, 0.0F, 0.85F);

        DrawRectangle(
            static_cast<int>(x),
            static_cast<int>(y),
            static_cast<int>(std::ceil(column_width)) + 1,
            static_cast<int>(wall_height),
            shade(wall.color, light));
    }

    DrawText("W/S move, <-/-> turn, A/D strafe, Up/Down look, Shift faster, Tab view", 16, 16, 20, RAYWHITE);

}
