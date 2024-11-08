precision mediump float;

uniform vec2  uResolution;
uniform vec2  uZoomCenter;
uniform float uZoomSize;
uniform vec2  uJuliaConstant;

const int maxIterations = 100;

void main() {
    vec2 uv = gl_FragCoord.xy / uResolution;
    vec2 z  = uZoomCenter + (uv * 4.0 - vec2(2.0)) * (uZoomSize / 4.0); // Start position for Julia Set

    int lastIteration = 0;

    for (int iteration = 0; iteration < maxIterations; iteration++) {
        lastIteration = iteration;
        if (length(z) > 2.0)
            break;
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + uJuliaConstant; // Use constant for Julia Set
    }

    float colorValue = float(lastIteration) / float(maxIterations);
    gl_FragColor = vec4(vec3(colorValue), 1.0);
}

