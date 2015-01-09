#version 420 core

//layout (binding = 5) uniform sampler2D material;

out vec4 color;
in vec3 vertexNormal;
//smooth in vec2 tc;

void main()
{
	vec3 lightDirection = vec3(1.0f, 1.0f, 1.0f);
	float diffuse = max(0.0f, dot(vertexNormal, lightDirection));

	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	vec3 scatteredLight = lightColor * diffuse;

	vec4 meshColor = vec4(0.4f, 0.5f, 0.1f, 1.0f);
	vec3 rgb = min(meshColor.rgb * scatteredLight, vec3(1.0));
	color = vec4(rgb, meshColor.a);
}
