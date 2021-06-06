#pragma once
#include "Singleton.h"
#include "RenderComponent.h"
#include "Minigin.h"

struct SDL_Window;
struct SDL_Renderer;

	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void RenderUI() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, float x, float y, Rect srcRect) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
		SDL_Window* GetWindow() const { return m_Window; }
	protected:
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window;

		bool* m_ShowDemo;
	};

