#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextRenderComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

dae::TextRenderComponent::TextRenderComponent(const std::string& text, const std::shared_ptr<Font>& font, GameObject* parent)
	: BaseComponent(parent)
	, m_Text(text)
	, m_Font(font)
	, m_pTexture(nullptr)
	, m_NeedsUpdate(true)
{
}

dae::TextRenderComponent::~TextRenderComponent()
{
}

void dae::TextRenderComponent::Update(float deltaTime)
{
	if (m_NeedsUpdate)
	{
		deltaTime;
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextRenderComponent::Render() const
{
	if (m_pTexture != nullptr)
	{
		const auto pos = m_Transform.GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void dae::TextRenderComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}
