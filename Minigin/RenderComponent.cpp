#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::RenderComponent::RenderComponent(GameObject* parent)
	:BaseComponent(parent)
{
}

dae::RenderComponent::~RenderComponent()
{
}

void dae::RenderComponent::Update(float deltaTime)
{
	deltaTime;
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::Render() const
{
	const auto pos = m_Transform.GetPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}
