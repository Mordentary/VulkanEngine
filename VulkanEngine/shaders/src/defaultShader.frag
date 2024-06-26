#version 450

layout(location = 0) out vec4 fragColor;



layout(location = 0) in vec3 v_VertColor;
layout(location = 1) in vec2 v_TextureCoord;

layout(binding = 1) uniform sampler2D textureSampler;

void main()
{
   fragColor = vec4(vec3(texture(textureSampler, v_TextureCoord) *  vec4(v_VertColor, 1.0f)),1.0f);
}