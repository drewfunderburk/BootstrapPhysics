#version 410

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;

uniform mat4 projectionViewModel;

out vec4 fColor;

void main()
{
	fColor = vColor;
	gl_Position = projectionViewModel * vPosition;
}