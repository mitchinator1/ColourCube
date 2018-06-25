#shader vertex
#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec4 inColour;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

out vec3 fragPos;
out vec3 normal;
out vec4 colour;

void main()
{
	fragPos = vec3(u_Model * vec4(inPosition, 1.0));
    normal = mat3(transpose(inverse(u_Model))) * inNormal;  
	colour = inColour;
    
    gl_Position = u_Projection * u_View * vec4(fragPos, 1.0);
}

#shader fragment
#version 330 core

out vec4 fragColour;

in vec3 normal;  
in vec3 fragPos;  
in vec4 colour;
  
uniform vec3 u_LightPos; 
uniform vec3 u_ViewPos; 
uniform vec3 u_LightColour;

void main()
{
    // ambient
    float ambientStrength = 0.85;
    vec3 ambient = ambientStrength * u_LightColour;
  	
    // diffuse 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(u_LightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_LightColour;
    
    // specular
    float specularStrength = 0.6;
    vec3 viewDir = normalize(u_ViewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * u_LightColour;  
        
    vec3 result = (ambient + diffuse + specular) * colour.xyz;
    fragColour = vec4(result, colour.a);
}
