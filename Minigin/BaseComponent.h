#pragma once
#include "Transform.h"

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent(GameObject* parent);
		virtual ~BaseComponent();
		virtual void Update(float deltaTime) = 0;
		virtual void Render() const = 0;
		void SetPosition(float x, float y);
	protected:
		dae::Transform m_Transform;
		GameObject* m_Parent;
	};
}

