#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform float translation;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    gl_Position.y *= -1;
    gl_Position.x += translation;
    ourColor = gl_Position.xyz;
}