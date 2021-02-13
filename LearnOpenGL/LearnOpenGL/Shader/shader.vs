#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 texCoord;
out vec3 viewNormal;
out vec3 viewPos;
out vec3 viewLightPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

void main()
{
	mat4 modelViewMatrix = view * model;

    gl_Position = projection * modelViewMatrix * vec4(aPos, 1.0);

	texCoord = aTexCoord;
	mat3 normalMatrix = transpose(inverse(mat3(modelViewMatrix)));
	viewNormal = normalMatrix * aNormal;
	viewPos = vec3(modelViewMatrix * vec4(aPos,1.0));
	viewLightPos = vec3(view * vec4(lightPos,1.0));
}