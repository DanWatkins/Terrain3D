#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;


uniform mat4 matrix_cameraToClip;
uniform mat4 matrix_modelToWorld;
uniform mat4 matrix_worldToCamera;

out vec4 shaderColor;

void main()
{
	//vec4 temp = matrix_modelToWorld * position;
	//temp = matrix_worldToCamera * temp;
	//gl_Position = matrix_cameraToClip * temp;

	gl_Position = vec4(position, 1.0f);

	shaderColor = vec4(color.x, color.y, color.z, 1.0f);
}