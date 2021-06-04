#pragma once
#include "BaseComponent.h"
#include "Helpers.h"
#include <iostream>


	class Texture2D;
	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent(GameObject* parent);
		~RenderComponent();

		void Update(float deltaTime) override;
		void SetTexture(const std::string& filename);
		std::string GetTexture() const;
		void SetSourceRect(int x, int y, int width, int height);
		void Render() const override;
	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		std::string m_TextureName;
		Rect m_SourceRect{};
	};


