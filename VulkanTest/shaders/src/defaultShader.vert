#version 450

layout(binding = 0) uniform  UniformBufferObject 
{
    mat4 model; 
    mat4 view; 
    mat4 proj; 
}ubo;

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec3 inColor;


layout(location = 0) out vec3 vertColor;

void main()
{
    gl_Position =  ubo.proj * ubo.view * ubo.model * vec4(inPos, 0.0, 1.0);
    vertColor = inColor;
}