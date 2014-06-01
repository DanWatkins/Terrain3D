#version 420 core

void main()
{	
	const vec4 vertices[] = vec4[](	vec4( 0.75, -0.75, 0.5, 1.0),
									vec4(-0.75, -0.75, 0.5, 1.0),
									vec4( 0.75,  0.75, 0.5, 1.0));

	gl_Position = vertices[gl_VertexID];
}