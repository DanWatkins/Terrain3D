#version 420 core

layout (binding = 5) uniform sampler2D material;

out vec4 color;
in vec3 vertexNormal;
in vec2 tc;

void main()
{
	vec3 lightDirection = vec3(1.0f, 1.0f, 1.0f);
	float diffuse = max(0.0f, dot(vertexNormal, lightDirection));

	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	vec3 scatteredLight = lightColor * diffuse;

	vec4 meshColor = texture(material, vec2(0.1f, 0.1f));
	//vec3 rgb = min(meshColor.rgb * scatteredLight, vec3(1.0));
	//color = vec4(rgb, meshColor.a);
	color = meshColor;
	
	//color = texelFetch(material, ivec2(5, 5), 0);
}
