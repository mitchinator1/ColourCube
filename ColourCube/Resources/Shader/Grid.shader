#shader vertex
#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColour;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

out vec3 colour;
out vec3 fragPos;

void main()
{
	colour = inColour;

    vec3 fragPos = vec3(u_Model * vec4(inPosition, 1.0));
    gl_Position = u_Projection * u_View * vec4(fragPos, 1.0);
}

#shader fragment
#version 330 core

in vec3 colour;

out vec4 fragColour;

void main()
{
    fragColour = vec4(colour, 1.0);
}
