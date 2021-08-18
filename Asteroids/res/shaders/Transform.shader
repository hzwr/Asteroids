#shader vertex
#version 330

uniform mat4 u_worldTransform;
uniform mat4 u_viewProj;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_texCoord;

out vec2 out_texCoord;
out vec3 out_worldNormal;
out vec3 out_worldPos;

void main()
{

	vec4 pos = vec4(in_position, 1.0);
	gl_Position = pos * u_worldTransform * u_viewProj;
	//gl_Position = pos;

	pos = pos * u_worldTransform;
	out_worldPos = pos.xyz;

	out_worldNormal = (vec4(in_normal, 0.0f) * u_worldTransform).xyz;

	out_texCoord = in_texCoord;
}

#shader fragment
#version 330 core

struct DirectionalLight
{
	vec3 m_direction;
	vec3 m_diffuseColor;
	vec3 m_specColor;
};

layout(location = 0) out vec4 out_color;

in vec2 out_texCoord;
in vec3 out_worldNormal;
in vec3 out_worldPos;

uniform vec4 u_color;
uniform sampler2D texture_diffuse1;
uniform vec3 u_cameraPos;
uniform vec3 u_ambientLight;
uniform float u_specPower;
uniform DirectionalLight u_dirLight;

void main()
{
	vec3 N = normalize(out_worldNormal);
	vec3 L = normalize(-u_dirLight.m_direction);
	vec3 V = normalize(u_cameraPos - out_worldPos);
	vec3 R = normalize(reflect(-L, N));

	vec3 Phong = u_ambientLight;
	float NdotL = dot(N, L);
	if (NdotL > 0)
	{
		vec3 Diffuse = u_dirLight.m_diffuseColor * NdotL;
		vec3 Specular = u_dirLight.m_specColor * pow(max(0.0, dot(R, V)), u_specPower);
		Phong += Diffuse;
	}

	//out_color = texture(texture_diffuse1, out_texCoord) * vec4(Phong, 1.0f);;
	vec2 texCoord = vec2(out_texCoord.x, 1.0 - out_texCoord.y);
	out_color = texture(texture_diffuse1, texCoord) * vec4(Phong, 1.0f);
	//out_color = vec4(0.1, 0.8, 0.8, 1.0);
};