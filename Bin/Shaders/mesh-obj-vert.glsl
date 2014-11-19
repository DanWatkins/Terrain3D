#version 420 core

layout (location = 0) in vec4 pos;

void main()
{
	float scale = 0.3f;
	gl_Position = vec4(pos.x*scale, pos.y*scale, pos.z*scale, pos.w);
}
