#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"


unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

bool Scene::IsActive() const
{
	return m_Active;
}

void Scene::SetActive(bool active)
{
	m_Active = active;
}

std::string Scene::GetSceneName() const
{
	return m_Name;
}

