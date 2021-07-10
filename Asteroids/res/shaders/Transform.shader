#shader vertex
#version 330

uniform mat4 u_worldTransform;
uniform mat4 u_viewProj;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

out vec2 v_texCoord;


void main()
{
	vec4 pos = vec4(inPosition, 1.0);
	gl_Position = pos * u_worldTransform * u_viewProj;

	v_texCoord = inTexCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 outColor;

in vec2 v_texCoord;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main()
{
	vec4 texColor = texture(u_texture, v_texCoord);
	outColor = texColor;
};