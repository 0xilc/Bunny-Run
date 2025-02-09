#version 330 core


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec4 pos;

void main()
{	
	pos = model * vec4(aPos, 1);
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}