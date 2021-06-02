#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{
	for(size_t i = 0; i < m_Components.size(); ++i)
	{
		delete m_Components[i];
	}
}

void dae::GameObject::AddComponent(BaseComponent* comp)
{
	m_Components.push_back(comp);
}

void dae::GameObject::Update(float deltaTime)
{
	// Loop over all the gameObjects and update them
	for(size_t i = 0; i < m_Components.size(); ++i)
	{
		m_Components[i]->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	const auto pos = m_Transform.GetPosition();
	for(size_t i = 0; i < m_Components.size(); ++i)
	{
		// Currently only rendering rendering components, the rendering function being virtual allows for future debug rendering of other components
		if(dynamic_cast<RenderComponent*>(m_Components[i])) 
		{
			m_Components[i]->Render();
		}
		else if (dynamic_cast<TextRenderComponent*>(m_Components[i]))
		{
			m_Components[i]->Render();
		}
	}
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

std::vector<dae::BaseComponent*> dae::GameObject::GetComponents() const
{
	return m_Components;
}
