#include "MiniginPCH.h"
#include <SDL.h>

#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"


RenderComponent::RenderComponent(GameObject* parent)
	:BaseComponent(parent)
	, m_SourceRect()
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::Update(float deltaTime)
{
	deltaTime;
}

void RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
	SDL_QueryTexture(m_pTexture.get()->GetSDLTexture(), NULL, NULL, &m_SourceRect.w, &m_SourceRect.h);
}

void RenderComponent::SetSourceRect(int x, int y, int width, int height)
{
	m_SourceRect.x = x;
	m_SourceRect.y = y;
	m_SourceRect.w = width;
	m_SourceRect.h = height;
}

void RenderComponent::Render() const
{
	const auto pos = m_Transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, m_SourceRect);
}
