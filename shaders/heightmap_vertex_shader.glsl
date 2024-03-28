#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec3 Normal;
out vec3  Position;
out vec4 ModelPosition;

void main()
{
	ModelPosition = model * vec4(position.xyz, 1.0);

	Position = vec4(projection * vec4(position, 1.0f)).xyz;
	gl_Position =  projection * view *  model * vec4(position, 1.0f);

	Normal = vec4(transpose(inverse(model)) * vec4(normal, 1.0f)).xyz;
}