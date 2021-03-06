#shader vertex
#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColour;

out vec4 colour;

void main()
{
	colour = inColour;
    
    gl_Position = vec4(inPosition, 1.0);
}

#shader fragment
#version 330 core

in vec4 colour;

out vec4 fragColour;

void main()
{
    fragColour = colour;
}
