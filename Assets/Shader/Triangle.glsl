// vertex shader
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_Tiling;

layout(location = 0) out vec4 v_Color;
layout(location = 1) out vec2 v_TexCoord;
layout(location = 2) out flat int v_TexIndex;
layout(location = 3) out flat float v_Tiling;

layout(std140, binding = 0) uniform Camera
{
    mat4 u_ViewProjectionMatrix;
};

void main()
{
    v_Color = a_Color;
    v_TexCoord = a_TexCoord;
    v_TexIndex = int(a_TexIndex);
    v_Tiling = a_Tiling;

    gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0f);
}

// fragment shader
#version 450 core

layout(location = 0) out vec4 o_Color;

layout(location = 0) in vec4 v_Color;
layout(location = 1) in vec2 v_TexCoord;
layout(location = 2) in flat int v_TexIndex;
layout(location = 3) in flat float v_Tiling;

// 32 seems to be the maximum number of textures that can be bound to a shader
// I guess it can differ but thats overall a good number
layout (binding = 0) uniform sampler2D u_Textures[32];

void main()
{
    vec4 texColor = v_Color;

    switch(v_TexIndex)
    {
        case  0: texColor *= texture(u_Textures[ 0], v_TexCoord * v_Tiling); break;
        case  1: texColor *= texture(u_Textures[ 1], v_TexCoord * v_Tiling); break;
        case  2: texColor *= texture(u_Textures[ 2], v_TexCoord * v_Tiling); break;
        case  3: texColor *= texture(u_Textures[ 3], v_TexCoord * v_Tiling); break;
        case  4: texColor *= texture(u_Textures[ 4], v_TexCoord * v_Tiling); break;
        case  5: texColor *= texture(u_Textures[ 5], v_TexCoord * v_Tiling); break;
        case  6: texColor *= texture(u_Textures[ 6], v_TexCoord * v_Tiling); break;
        case  7: texColor *= texture(u_Textures[ 7], v_TexCoord * v_Tiling); break;
        case  8: texColor *= texture(u_Textures[ 8], v_TexCoord * v_Tiling); break;
        case  9: texColor *= texture(u_Textures[ 9], v_TexCoord * v_Tiling); break;
        case 10: texColor *= texture(u_Textures[10], v_TexCoord * v_Tiling); break;
        case 11: texColor *= texture(u_Textures[11], v_TexCoord * v_Tiling); break;
        case 12: texColor *= texture(u_Textures[12], v_TexCoord * v_Tiling); break;
        case 13: texColor *= texture(u_Textures[13], v_TexCoord * v_Tiling); break;
        case 14: texColor *= texture(u_Textures[14], v_TexCoord * v_Tiling); break;
        case 15: texColor *= texture(u_Textures[15], v_TexCoord * v_Tiling); break;
        case 16: texColor *= texture(u_Textures[16], v_TexCoord * v_Tiling); break;
        case 17: texColor *= texture(u_Textures[17], v_TexCoord * v_Tiling); break;
        case 18: texColor *= texture(u_Textures[18], v_TexCoord * v_Tiling); break;
        case 19: texColor *= texture(u_Textures[19], v_TexCoord * v_Tiling); break;
        case 20: texColor *= texture(u_Textures[20], v_TexCoord * v_Tiling); break;
        case 21: texColor *= texture(u_Textures[21], v_TexCoord * v_Tiling); break;
        case 22: texColor *= texture(u_Textures[22], v_TexCoord * v_Tiling); break;
        case 23: texColor *= texture(u_Textures[23], v_TexCoord * v_Tiling); break;
        case 24: texColor *= texture(u_Textures[24], v_TexCoord * v_Tiling); break;
        case 25: texColor *= texture(u_Textures[25], v_TexCoord * v_Tiling); break;
        case 26: texColor *= texture(u_Textures[26], v_TexCoord * v_Tiling); break;
        case 27: texColor *= texture(u_Textures[27], v_TexCoord * v_Tiling); break;
        case 28: texColor *= texture(u_Textures[28], v_TexCoord * v_Tiling); break;
        case 29: texColor *= texture(u_Textures[29], v_TexCoord * v_Tiling); break;
        case 30: texColor *= texture(u_Textures[30], v_TexCoord * v_Tiling); break;
        case 31: texColor *= texture(u_Textures[31], v_TexCoord * v_Tiling); break;
    }

    if (texColor.a == 0.0)
    discard;

    o_Color = texColor;
}