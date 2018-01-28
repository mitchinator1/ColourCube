#shader vertex
#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColour;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

out vec4 colour;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(inPosition, 1.0);
	colour = vec4(inColour, 1.0);
};

#shader fragment
#version 330 core

out vec4 fragColour;
in vec4 colour;

void main()
{
	fragColour = colour;
};
