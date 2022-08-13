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

//https://www.shadertoy.com/view/Mtj3Dd

float distanceToLine(vec2 p1, vec2 p2, vec2 point) {
    float a = p1.y-p2.y;
    float b = p2.x-p1.x;
    return abs(a*point.x+b*point.y+p1.x*p2.y-p2.x*p1.y) / sqrt(a*a+b*b);
}

vec2 midpoint (vec2 p1, vec2 p2)
{
    return vec2((p1.x+p2.x)/2., (p1.y+p2.y) /2.);

}

float clampToLine (vec2 p1, vec2 p2, vec2 point, float line)
{
    vec2 mp = midpoint(p1,p2);
    float maxDistance = distance(mp,p1);
    if (distance(mp,point) > maxDistance)
    {
        return 0.;
    }
    else
    {
        return line;
    }

}

void main()
{
    vec2 uv = v_InterpolatingPosition;
    // get distance to line
    float distance = distanceToLine (v_PosA.xy,v_PosB.xy,uv);
    //line
    float radius = v_Thickness;
    float line =  smoothstep (radius/2., radius/2.-0.00001, distance);

    line =  clampToLine(v_PosA.xy, v_PosB.xy, uv, line);


    float outLine = line;

    if (outLine < 0.5)
    {
        o_Color = vec4(0.,0.,0.,0.);
        discard;
    }
    o_Color = vec4(1.*outLine, 1.*outLine, 1.*outLine, 1.0) * v_Color;
}