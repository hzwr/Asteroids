#pragma once
#include <string>

enum class TextureType
{
	EDiffuse,
	ESpecular
};

class Texture
{
public:
	Texture();
	~Texture();

	//Delete the copy constructor/assignment.
	Texture(const Texture &) = delete;
	Texture &operator=(const Texture &) = delete;
	// TODO: rule of 3/5/0

	bool Load(const std::string &fileName);
	void Unload();
	void CreateFromSurface(struct SDL_Surface *surface);

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

	TextureType GetTextureType() const { return m_textureType; }
	void SetTextureType(TextureType type) { m_textureType = type; }
private:
	TextureType m_textureType = TextureType::EDiffuse;
	unsigned int m_textureID = 0;
	int mWidth;
	int mHeight;
};
