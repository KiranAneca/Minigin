#pragma once
#include "Transform.h"
#include "Helpers.h"

	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent(GameObject* parent);
		virtual ~BaseComponent();
		virtual void Update(float deltaTime) = 0;
		virtual void Render() const = 0;
		
		void SetPosition(float x, float y);
		float2 GetPosition() const;
	protected:
		Transform m_Transform;
		GameObject* m_Parent;
	};

