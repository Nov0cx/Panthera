#type vertex
#version 450

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in float inTexIndex;
layout(location = 4) in float inTilingFactor;

layout(location = 0) out vec4 outColor;
layout(location = 1) out vec2 outTexCoord;
layout(location = 2) out flat float outTexIndex;
layout(location = 3) out flat float outTilingFactor;

void main()
{
    outColor = inColor;
    outTexCoord = inTexCoord;
    outTexIndex = inTexIndex;
    outTilingFactor = inTilingFactor;
    gl_Position = vec4(inPosition, 1.0);
}

#type fragment
#version 450

layout(location = 0) in vec4 inColor;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in flat float inTexIndex;
layout(location = 3) in flat float inTilingFactor;

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D u_Textures[32];

void main()
{
    vec4 color = inColor;

    switch (int(inTexIndex))
    {
        case  0: color *= texture(u_Textures[0], inTexCoord * inTilingFactor); break;
        case  1: color *= texture(u_Textures[1], inTexCoord * inTilingFactor); break;
        case  2: color *= texture(u_Textures[2], inTexCoord * inTilingFactor); break;
        case  3: color *= texture(u_Textures[3], inTexCoord * inTilingFactor); break;
        case  4: color *= texture(u_Textures[4], inTexCoord * inTilingFactor); break;
        case  5: color *= texture(u_Textures[5], inTexCoord * inTilingFactor); break;
        case  6: color *= texture(u_Textures[6], inTexCoord * inTilingFactor); break;
        case  7: color *= texture(u_Textures[7], inTexCoord * inTilingFactor); break;
        case  8: color *= texture(u_Textures[8], inTexCoord * inTilingFactor); break;
        case  9: color *= texture(u_Textures[9], inTexCoord * inTilingFactor); break;
        case 10: color *= texture(u_Textures[10], inTexCoord * inTilingFactor); break;
        case 11: color *= texture(u_Textures[11], inTexCoord * inTilingFactor); break;
        case 12: color *= texture(u_Textures[12], inTexCoord * inTilingFactor); break;
        case 13: color *= texture(u_Textures[13], inTexCoord * inTilingFactor); break;
        case 14: color *= texture(u_Textures[14], inTexCoord * inTilingFactor); break;
        case 15: color *= texture(u_Textures[15], inTexCoord * inTilingFactor); break;
        case 16: color *= texture(u_Textures[16], inTexCoord * inTilingFactor); break;
        case 17: color *= texture(u_Textures[17], inTexCoord * inTilingFactor); break;
        case 18: color *= texture(u_Textures[18], inTexCoord * inTilingFactor); break;
        case 19: color *= texture(u_Textures[19], inTexCoord * inTilingFactor); break;
        case 20: color *= texture(u_Textures[20], inTexCoord * inTilingFactor); break;
        case 21: color *= texture(u_Textures[21], inTexCoord * inTilingFactor); break;
        case 22: color *= texture(u_Textures[22], inTexCoord * inTilingFactor); break;
        case 23: color *= texture(u_Textures[23], inTexCoord * inTilingFactor); break;
        case 24: color *= texture(u_Textures[24], inTexCoord * inTilingFactor); break;
        case 25: color *= texture(u_Textures[25], inTexCoord * inTilingFactor); break;
        case 26: color *= texture(u_Textures[26], inTexCoord * inTilingFactor); break;
        case 27: color *= texture(u_Textures[27], inTexCoord * inTilingFactor); break;
        case 28: color *= texture(u_Textures[28], inTexCoord * inTilingFactor); break;
        case 29: color *= texture(u_Textures[29], inTexCoord * inTilingFactor); break;
        case 30: color *= texture(u_Textures[30], inTexCoord * inTilingFactor); break;
        case 31: color *= texture(u_Textures[31], inTexCoord * inTilingFactor); break;
    }

    if (color.a == 0)
        discard;

    outColor = color;
}