#include "FontType.h"
#include "GL/glew.h"
//#include "GLFW/glfw3.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../stb_image.h"
#include <iostream>

namespace Text
{
	FontType::FontType(const std::string& fontFile)
		: m_TextureAtlas(0), m_Loader(new TextMeshCreator("Resources/Font/" + fontFile + ".fnt"))
	{
		LoadTextureAtlas(fontFile);
	}

	FontType::~FontType()
	{
		delete m_Loader;
	}

	unsigned int FontType::GetTextureAtlas() const
	{
		return m_TextureAtlas;
	}

	TextMeshData FontType::LoadText(GUIText& text)
	{
		return m_Loader->CreateTextMesh(text);
	}

	void FontType::LoadTextureAtlas(const std::string& fontFile)
	{
		glGenTextures(1, &m_TextureAtlas);
		glBindTexture(GL_TEXTURE_2D, m_TextureAtlas);	// all upcoming GL_TEXTURE_2D operations now have effect on this texture object
														// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		int width, height, nrChannels;
		std::string filepath("Resources/Font/" + fontFile + ".png");

		unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}
}