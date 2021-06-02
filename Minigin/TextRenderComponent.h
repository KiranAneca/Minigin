#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class Font;
	class TextRenderComponent : public BaseComponent
	{
	public:
		TextRenderComponent(const std::string& text, const std::shared_ptr<Font>& font, GameObject* parent);
		~TextRenderComponent();

		void Update(float deltaTime) override;
		void Render() const override;

		void SetText(const std::string& text);
	
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Texture2D> m_pTexture{};
		std::shared_ptr<Font> m_Font;
	};
}

