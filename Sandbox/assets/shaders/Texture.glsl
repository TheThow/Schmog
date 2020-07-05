#type vertex
#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;
layout (location = 2) in vec4 a_Color;
layout (location = 3) in uint a_TexIndex;

uniform mat4 u_ViewProjection;

out vec2 v_TexCoord; 
out vec4 v_Color;
flat out uint v_TexIndex;

uniform uint u_Color;

void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);

	v_Color = a_Color;

	v_TexIndex = a_TexIndex;
}


#type fragment
#version 330 core

layout(location = 0) out vec4 o_Color;

in vec2 v_TexCoord;
in vec4 v_Color;
flat in uint v_TexIndex;

uniform sampler2D u_Texture[32];

void main()
{
	o_Color = texture(u_Texture[int(v_TexIndex)], v_TexCoord) * v_Color;
}