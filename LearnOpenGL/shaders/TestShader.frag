#version 330 core

out vec4 FragColor;
in vec3 ourColor;

uniform vec3 colorMask;

void main()
{
	FragColor = vec4(ourColor * colorMask, 1.0f);
}