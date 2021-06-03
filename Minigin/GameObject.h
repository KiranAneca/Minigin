#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include <vector>
// Components
#include "BaseComponent.h"
#include "TextRenderComponent.h"

	class Texture2D;
	class GameObject final : public SceneObject
	{
	public:
		void Update(float deltaTime) override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		std::vector<BaseComponent*> GetComponents() const;
		template <typename T> T* GetComponent() const;

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void AddComponent(BaseComponent* comp);

	private:
		Transform m_Transform;
		
		std::shared_ptr<Texture2D> m_Texture{};
		std::vector<BaseComponent*> m_Components;
	};

	template <typename T>
	T* GameObject::GetComponent() const
	{
		for(BaseComponent * comp: m_Components)
		{
			if(dynamic_cast<T*>(comp) != nullptr)
			{
				return (T*)comp;
			}
		}
		return nullptr;
	}
