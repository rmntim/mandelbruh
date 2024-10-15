#ifndef SHADER_H_
#define SHADER_H_

const char *SHADER_CODE =
#if defined(PLATFORM_DESKTOP)
    "#version 330 core\n"
    "\n"
    "uniform vec2  uResolution\n;
    "uniform vec2  uZoomCenter;\n"
    "uniform float uZoomSize;\n"
    "uniform int   uMaxIterations;\n"
    "\n"
    "out vec4 finalColor\n;
    "\n"
    "void main() \n{
    "    vec2 uv = gl_FragCoord.xy / uResolution;\n"
    "    vec2 c  = uZoomCenter + (uv * 4.0 - vec2(2.0)) * (uZoomSize / 4.0);\n"
    "    vec2 z  = vec2(0.0);\n"
    "\n"
    "    int iteration = 0\n;
    "\n"
    "    for (iteration = 0; iteration < uMaxIterations; iteration++) \n{
    "        if (length(z) > 2.0)\n"
    "            break;\n"
    "        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;\n"
    "    }\n"
    "\n"
    "    float colorValue = float(iteration) / float(uMaxIterations)\n;
    "    finalColor = vec4(vec3(colorValue), 1.0);\n"
    "}";
#else
    "precision mediump float;\n"
    "\n"
    "uniform vec2  uResolution;\n"
    "uniform vec2  uZoomCenter;\n"
    "uniform float uZoomSize;\n"
    "const   int   maxIterations = 100;\n"
    "\n"
    "void main() {\n"
    "    vec2 uv = gl_FragCoord.xy / uResolution;\n"
    "    vec2 c  = uZoomCenter + (uv * 4.0 - vec2(2.0)) * (uZoomSize / 4.0);\n"
    "    vec2 z  = vec2(0.0);\n"
    "\n"
    "    int lastIteration = 0;\n"
    "\n"
    "    for (int iteration = 0; iteration < maxIterations; iteration++) {\n"
    "        lastIteration = iteration;\n"
    "        if (length(z) > 2.0)\n"
    "            break;\n"
    "        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;\n"
    "    }\n"
    "\n"
    "    float colorValue = float(lastIteration) / float(maxIterations);\n"
    "    gl_FragColor = vec4(vec3(colorValue), 1.0);\n"
    "}";
#endif

#endif // SHADER_H_"
