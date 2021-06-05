#pragma once
#include "Renderer.h"
#include "Singleton.h"
#include "Application.h"
class GameRenderer : public Singleton<GameRenderer>
{
public:
	void Init(SDL_Window* window);
	void Render() const;
	void RenderUI(Application* app) const;
	void Destroy();

	void RenderTexture(const Texture2D& texture, float x, float y) const;
	void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
	void RenderTexture(const Texture2D& texture, float x, float y, Rect srcRect) const;
private:
	SDL_Window* m_Window;
};

