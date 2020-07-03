#type vertex
#version 330 core

layout (location = 0) in vec2 a_Translation;
layout (location = 1) in float a_ZCoordinate;
layout (location = 2) in float a_Rotation;
layout (location = 3) in vec4 a_Color;
layout (location = 4) in vec2 a_Scale;
layout (location = 5) in vec2 a_TexCoord;
layout (location = 6) in float a_TexIndex;
layout (location = 7) in float a_TilingFactor;

uniform mat4 u_ViewProjection;

out vec2 v_TexCoord; 
out vec4 v_Color;
out float v_TexIndex;
out float v_TilingFactor;

in int gl_VertexID;

vec4 vertexPositions[] = vec4[4]
(
	vec4(-0.5, -0.5, a_ZCoordinate, 1.0),
	vec4(0.5, -0.5, a_ZCoordinate, 1.0),
	vec4(0.5, 0.5, a_ZCoordinate, 1.0),
	vec4(-0.5, 0.5, a_ZCoordinate, 1.0)
);


void main()
{
	v_TexCoord = a_TexCoord;

	int vertexIndex = gl_VertexID % 4;
	vec4 vertexPosition = vertexPositions[vertexIndex];

	vertexPosition[0] = 1.0f * (cos(a_Rotation) * vertexPositions[vertexIndex][0] - sin(a_Rotation) * vertexPositions[vertexIndex][1]) + a_Translation[0];
	vertexPosition[1] = 1.0f * (sin(a_Rotation) * vertexPositions[vertexIndex][0] + cos(a_Rotation) * vertexPositions[vertexIndex][1]) + a_Translation[1];


	gl_Position = u_ViewProjection * vertexPosition;
	v_Color = a_Color;
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

uniform vec4 u_Color;
uniform sampler2D u_Texture[32];

void main()
{
	o_Color = texture(u_Texture[int(v_TexIndex)], v_TexCoord * v_TilingFactor) * v_Color;
}