#pragma once
#include <string>

class Texture
{
public:
	Texture();
	~Texture();

	bool Load(const std::string &fileName);
	void Unload();
	void CreateFromSurface(struct SDL_Surface *surface);

	void SetActive();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
private:
	unsigned int m_textureID;
	int mWidth;
	int mHeight;
};
