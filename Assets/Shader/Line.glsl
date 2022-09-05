// vertex shader
#version 450 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_PosA;
layout (location = 2) in vec3 a_PosB;
layout (location = 3) in vec2 a_InterpolatingPosition;
layout (location = 4) in float a_Thickness;
layout (location = 5) in vec4 a_Color;

layout (location = 0) out vec2 v_InterpolatingPosition;
layout (location = 1) out flat vec3 v_PosA;
layout (location = 2) out flat vec3 v_PosB;
layout (location = 3) out flat float v_Thickness;
layout (location = 4) out vec4 v_Color;

layout(std140, binding = 0) uniform Camera
{
    mat4 u_ViewProjectionMatrix;
};

void main()
{
    v_InterpolatingPosition = a_InterpolatingPosition;
    v_PosA = a_PosA;
    v_PosB = a_PosB;
    v_Thickness = a_Thickness;
    v_Color = a_Color;

    gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
}

// fragment shader
#version 450 core

layout (location = 0) in vec2 v_InterpolatingPosition;
layout (location = 1) in flat vec3 v_PosA;
layout (location = 2) in flat vec3 v_PosB;
layout (location = 3) in flat float v_Thickness;
layout (location = 4) in vec4 v_Color;

layout (location = 0) out vec4 o_Color;


void main()
{
    vec2 uv = v_InterpolatingPosition;

    vec2 p1 = v_PosA.xy;
    vec2 p2 = v_PosB.xy;
    float thickness = v_Thickness;

    vec2 p12 = p2 - p1;
    vec2 p13 = uv - p1;

    float d = dot(p12, p13) / length(p12);
    vec2 p = p1 + normalize(p12) * d;

    if (length(p - uv) > thickness)
    {
        o_Color = vec4(0.,0.,0.,0.);
        discard;
    }
    o_Color = v_Color;
}