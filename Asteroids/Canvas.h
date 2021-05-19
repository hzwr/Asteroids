#pragma once
#include <cstdint>
#include <string>
#include <functional>
#include <vector>
#include "Math.h"

class Button
{
public:
	Button(const std::string &name, class Font *font,
		std::function<void()> onClick,
		const Vector2 &pos, const Vector2 &dims);
	~Button();

	// Set the name of the button
	void SetName(const std::string &name);

	class Texture *GetNameTex() { return mNameTex; }
	const Vector2 &GetPosition() const { return mPosition; }
	void SetHighlighted(bool sel) { mHighlighted = sel; }
	bool GetHighlighted() const { return mHighlighted; }

	// Returns true if the point is within the button's bounds
	bool ContainsPoint(const Vector2 &pt) const;
	// Called when button is clicked
	void OnClick();
private:
	std::function<void()> mOnClick;
	std::string mName;
	class Texture *mNameTex;
	class Font *mFont;
	Vector2 mPosition;
	Vector2 mDimensions;
	bool mHighlighted;
};

class Canvas
{
public:
	Canvas(class Game *game);
	virtual void Render();

protected:
	class Game *mGame;
	std::vector<Button *> mButtons;
	bool isActive;
};

