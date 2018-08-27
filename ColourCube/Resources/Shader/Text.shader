#shader vertex
#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoords;
layout(location = 2) in vec3 colour;

out vec2 pass_textureCoords;
out vec3 pass_colour;

void main()
{
	gl_Position = vec4(position, 1.0);
	pass_textureCoords = textureCoords;
	pass_colour = colour;
}

#shader fragment
#version 330

in vec2 pass_textureCoords;
in vec3 pass_colour;

out vec4 fragColour;

uniform sampler2D u_FontAtlas;

float width = 0.4f;
float edge = 0.1f;

float borderWidth = 0.6f;
float borderEdge = 0.1f;

vec3 outlineColour = vec3(0.0f, 0.0f, 0.0f);

void main()
{
	float distance1 = 1.0f - texture(u_FontAtlas, pass_textureCoords).a;
	float alpha1 = 1.0f - smoothstep(width, width + edge, distance1);

	float distance2 = 1.0f - texture(u_FontAtlas, pass_textureCoords).a;
	float outlineAlpha = 1.0f - smoothstep(borderWidth, borderWidth + borderEdge, distance2);

	float overallAlpha = alpha1 + (1.0 - alpha1) * outlineAlpha;
	vec3 overallColour = mix(outlineColour, pass_colour, alpha1 / overallAlpha);

	fragColour = vec4(overallColour, overallAlpha);
}
