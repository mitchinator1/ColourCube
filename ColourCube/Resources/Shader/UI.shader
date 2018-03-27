#shader vertex
#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColour;

out vec3 colour;

void main()
{
	colour = inColour;
    
    gl_Position = vec4(inPosition, 1.0);
}

#shader fragment
#version 330 core

out vec4 fragColour;

in vec3 colour;

void main()
{
    fragColour = vec4(colour.r, colour.g, colour.b, 1.0);
}
