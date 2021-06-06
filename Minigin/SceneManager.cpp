#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_Scenes)
	{
		if(scene->IsActive())
		{
			scene->Update(deltaTime);
		}
	}
}

void SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		if(scene->IsActive())
		{
			scene->Render();
		}
	}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

Scene& SceneManager::GetActiveScene() const
{
	for(size_t i = 0; i < m_Scenes.size(); ++i)
	{
		if(m_Scenes[i]->IsActive())
		{
			return *m_Scenes[i];
		}
	}
	return *m_Scenes[0];
}

void SceneManager::SetSceneActive(bool active, std::string name)
{
	for (size_t i = 0; i < m_Scenes.size(); ++i)
	{
		if (m_Scenes[i]->GetSceneName() == name)
		{
			m_Scenes[i]->SetActive(active);
		}
	}
}

void SceneManager::DeleteScene(std::string name)
{
	std::vector<std::shared_ptr<Scene>>::iterator iter = m_Scenes.end();
	for(auto it = m_Scenes.begin(); it != m_Scenes.end(); it++)
	{
		if(it->get()->GetSceneName() == name)
		{
			iter = it;
			break;
		}
	}
	if(iter != m_Scenes.end())m_Scenes.erase(iter);

}
