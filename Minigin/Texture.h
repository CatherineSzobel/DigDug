#pragma once
#include <string>
#include <iostream>
#include <SDL_ttf.h>
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"
#include "SDL_opengl.h"
#include "SDL.h"
#include "SDL_surface.h"
#include "SDL_image.h"
#include "ExtraStructs.h"
class Texture final
{
public:
	explicit Texture(const std::string& imagePath);
	Texture(const Texture& other) = delete;
	Texture& operator=(const Texture& other) = delete;
	Texture(Texture&& other) noexcept;
	Texture& operator=(Texture&& other) noexcept;
	~Texture();

	void Draw(const glm::vec2& dstBottomLeft = {}, const Rectf& srcRect = {}) const;
	void Draw(const Rectf& dstRect, const Rectf& srcRect = {}) const;

	float GetWidth() const { return m_Width; }
	float GetHeight() const { return m_Height; };
	bool IsCreationOk() const { return m_CreationOk; };

private:
	//DATA MEMBERS
	GLuint m_Id;
	float m_Width;
	float m_Height;
	bool m_CreationOk;

	// FUNCTIONS
	void CreateFromImage(const std::string& path);
	void CreateFromSurface(SDL_Surface* pSurface);
	void DrawFilledRect(const  Rectf& dstRect) const;
};
