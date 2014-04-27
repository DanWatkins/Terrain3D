#version 430 core

layout (location = 0) in vec4 position;

uniform mat4 matrix_cameraToClip;
uniform mat4 matrix_modelToWorld;
uniform mat4 matrix_worldToCamera;

out vec4 shaderColor;

void main()
{
	vec4 temp = matrix_modelToWorld * position;
	temp = matrix_worldToCamera * temp;
	gl_Position = matrix_cameraToClip * temp;

	shaderColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
}