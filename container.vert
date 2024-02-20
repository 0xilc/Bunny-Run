#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec4 fragWorldPos;
out vec3 fragWorldNor;

void main()
{
	fragWorldPos = model * vec4(aPos, 1);
	fragWorldNor = inverse(transpose(mat3x3(model))) * aNormal;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}