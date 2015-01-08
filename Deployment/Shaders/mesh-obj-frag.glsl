#version 420 core

out vec4 color;
in vec3 vertexNormal;

void main()
{
	color = vec4(vertexNormal.x, vertexNormal.y, vertexNormal.z, 1.0f);
}
