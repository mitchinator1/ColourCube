#shader vertex
#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textureCoords;

out vec2 pass_textureCoords;

void main()
{
	gl_Position = vec4(position, 0.0, 1.0);
	pass_textureCoords = textureCoords;
}

#shader fragment
#version 330

in vec2 pass_textureCoords;

out vec4 fragColour;

uniform vec3 u_Colour;
uniform sampler2D u_FontAtlas;

float width = 0.4f;
float edge = 0.1f;

float borderWidth = 0.6f;
float borderEdge = 0.1f;

vec3 outlineColour = vec3(0.0f, 0.0f, 0.0f);

void main()
{
	float distance = 1.0f - texture(u_FontAtlas, pass_textureCoords).a;
	float alpha = 1.0f - smoothstep(width, width + edge, distance);

	float distance2 = 1.0f - texture(u_FontAtlas, pass_textureCoords).a;
	float outlineAlpha = 1.0f - smoothstep(borderWidth, borderWidth + borderEdge, distance2);

	float overallAlpha = alpha + (1.0 - alpha) * outlineAlpha;
	vec3 overallColour = mix(outlineColour, u_Colour, alpha / overallAlpha);

	fragColour = vec4(overallColour, overallAlpha);
}
