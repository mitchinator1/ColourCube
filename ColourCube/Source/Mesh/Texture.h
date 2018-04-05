#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>

class Texture
{
private:
	unsigned int m_TextureID;

public:
	Texture(const std::string& filename);
	~Texture();
	
	void Bind() const;
	void Unbind() const;

	inline unsigned int GetTexture() const { return m_TextureID; }

private:
	void LoadImage(const std::string& filepath);
};

#endif