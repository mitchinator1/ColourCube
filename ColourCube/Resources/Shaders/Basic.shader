#shader vertex
#version 330 core

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColour;

out vec3 colour;

void main()
{
	gl_Position = vec4(inPosition, 0.0, 1.0);
	colour = inColour;
};

#shader fragment
#version 330 core

out vec4 fragColour;
in vec3 colour;

void main()
{
	fragColour = vec4(colour, 1.0);
};
