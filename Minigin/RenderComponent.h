#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent(GameObject* parent);
		~RenderComponent();

		void Update(float deltaTime) override;
		void SetTexture(const std::string& filename);
		void Render() const override;
	private:
		std::shared_ptr<Texture2D> m_pTexture{};
	};
}

