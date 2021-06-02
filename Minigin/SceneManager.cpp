#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

dae::Scene& dae::SceneManager::GetActiveScene() const
{
	for(int i = 0; i < m_Scenes.size(); ++i)
	{
		if(m_Scenes[i]->IsActive())
		{
			return *m_Scenes[i];
		}
	}
	return *m_Scenes[0];
}
