#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in float a_TilingFactor;
layout (location = 2) in uint a_Color;
layout (location = 3) in float a_TexIndex;
layout (location = 4) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;

out vec2 v_TexCoord; 
out vec4 v_Color;
out float v_TexIndex;
out float v_TilingFactor;

uniform uint u_Color;

void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);

	v_Color = vec4(((a_Color & uint(0xFF000000)) >> 24) / 255.f, 
					((a_Color & uint(0x00FF0000)) >> 16) / 255.f, 
					((a_Color & uint(0x0000FF00)) >> 8) / 255.f, 
					((a_Color & uint(0x000000FF))) / 255.f);

	v_TexIndex = a_TexIndex;
	v_TilingFactor = a_TilingFactor;
}


#type fragment
#version 330 core

layout(location = 0) out vec4 o_Color;

in vec2 v_TexCoord;
in vec4 v_Color;
in float v_TexIndex;
in float v_TilingFactor;

uniform sampler2D u_Texture[32];

void main()
{
	o_Color = texture(u_Texture[int(v_TexIndex)], v_TexCoord * v_TilingFactor) * v_Color;
}