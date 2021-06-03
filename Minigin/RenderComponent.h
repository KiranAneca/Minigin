#pragma once
#include "BaseComponent.h"
#include "Helpers.h"



	class Texture2D;
	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent(GameObject* parent);
		~RenderComponent();

		void Update(float deltaTime) override;
		void SetTexture(const std::string& filename);
		void SetSourceRect(int x, int y, int width, int height);
		void Render() const override;
	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		Rect m_SourceRect{};
	};


