#pragma once
#include "SceneManager.h"

	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<SceneObject>& object);

		void Update(float deltaTime);
		void Render() const;

		bool IsActive() const;
		void SetActive(bool active);
		std::string GetSceneName() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		bool m_Active = true;
		std::vector < std::shared_ptr<SceneObject>> m_Objects{};

		static unsigned int m_IdCounter; 
	};

