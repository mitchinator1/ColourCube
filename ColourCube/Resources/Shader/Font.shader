#shader vertex
#version 330

in vec2 position;
in vec2 textureCoords;

out vec2 pass_textureCoords;

uniform vec2 u_Translation;

void main(void){

	gl_Position = vec4(position + u_Translation * vec2(2.0, -2.0), 0.0, 1.0);
	pass_textureCoords = textureCoords;

}

#shader fragment
#version 330

in vec2 pass_textureCoords;

out vec4 fragColour;

uniform vec3 u_Colour;
uniform sampler2D u_FontAtlas;

void main(void){

	fragColour = vec4(u_Colour, texture(u_FontAtlas, pass_textureCoords).a);

};
