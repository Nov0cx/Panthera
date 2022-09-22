#type vertex
#version 450

layout(location = 0) in vec3 a_Position;

void main()
{
    gl_Position = vec4(a_Position, 1);
}

#type fragment
#version 450

layout(location = 0) out vec4 o_Color;

layout(std140, binding = 0) uniform Color
{
    vec4 u_Color;
};

void main()
{
    o_Color = u_Color;
}