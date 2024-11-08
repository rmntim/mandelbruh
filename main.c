#include <math.h>
#include <raylib.h>
#include <stdlib.h>

#if defined(WIN32) || defined(_WIN32)
#define SEP "\\"
#else
#define SEP "/"
#endif

#ifndef FRACTAL_TYPE
#define FRACTAL_TYPE "mandelbrot"
#endif

#define SHADER_DIR "shaders"

#if defined(PLATFORM_DESKTOP)
#define PLATFORM_FILE "desktop.glsl"
#elif defined(PLATFORM_WEB)
#define PLATFORM_FILE "web.glsl"
#endif

#ifndef PLATFORM_FILE
#error "No platform file can be determined"
#endif

const char *shaderPath = SHADER_DIR SEP FRACTAL_TYPE SEP PLATFORM_FILE;

int main() {
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, FRACTAL_TYPE " Set");

  Vector2 resolution = {screenWidth, screenHeight};

  Shader shader = LoadShader(NULL, shaderPath);

  // Set initial uniform values for the shader
  Vector2 zoomCenter = {-0.5f, 0.0f};
  float zoomSize = 3.0f;
  int maxIterations = 100;

  Vector2 lastMousePosition = {0.0f, 0.0f};
  bool isDragging = false;

  while (!WindowShouldClose()) {
    // Handle mouse wheel zooming
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      lastMousePosition = GetMousePosition();
      isDragging = true;
    }
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
      isDragging = false;
    }
    if (isDragging) {
      Vector2 currentMousePosition = GetMousePosition();
      Vector2 delta = {currentMousePosition.x - lastMousePosition.x,
                       currentMousePosition.y - lastMousePosition.y};

      // Adjust zoomCenter based on mouse drag
      zoomCenter.x -= delta.x * (zoomSize / screenWidth);
      zoomCenter.y += delta.y * (zoomSize / screenHeight); // Invert Y-axis
      lastMousePosition = currentMousePosition;
    }

    // Zoom in/out with mouse wheel
    float wheelMove = GetMouseWheelMove();
    if (wheelMove != 0) {
      zoomSize *= (wheelMove > 0) ? 0.9f : 1.1f; // Zoom in or out
    }

    double elapsedTime = GetTime() / 2;

    Vector2 juliaConstant = {cosf(elapsedTime), sinf(elapsedTime)};

    // Update shader uniforms
    SetShaderValue(shader, GetShaderLocation(shader, "uResolution"),
                   &resolution, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, GetShaderLocation(shader, "uZoomCenter"),
                   &zoomCenter, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, GetShaderLocation(shader, "uZoomSize"), &zoomSize,
                   SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, GetShaderLocation(shader, "uMaxIterations"),
                   &maxIterations, SHADER_UNIFORM_INT);
    SetShaderValue(shader, GetShaderLocation(shader, "uJuliaConstant"),
                   &juliaConstant, SHADER_UNIFORM_VEC2);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginShaderMode(shader);
    DrawRectangle(0, 0, screenWidth, screenHeight,
                  WHITE); // Draw fullscreen quad
    EndShaderMode();

    DrawText("Mandelbrot Set", 10, 10, 20, DARKGRAY);
    DrawText("Drag to pan and use mouse wheel to zoom", 10, 40, 20, DARKGRAY);

    DrawFPS(0, 0);

    EndDrawing();
  }

  UnloadShader(shader);
  CloseWindow(); // Close window and OpenGL context

  return 0;
}
