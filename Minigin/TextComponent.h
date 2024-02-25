#pragma once
#include "Component.h"
#include <string>
#include <memory>
#include "GameObject.h"
#include "TextureComponent.h"
#include "Font.h"
#include "Texture2D.h"



namespace dae
{

	class TextComponent : public Component
	{
	public:
		TextComponent(GameObject* pOwner, const std::string& stringText, std::shared_ptr<Font> font);
		~TextComponent() override = default;
		void Update(float) override;
		void SetText(const std::string& text);

	private:
		bool m_needsUpdate; //running ahead with dirty flag? asking in class if its okay to run ahead...
		std::string m_textString;
		std::shared_ptr<Font> m_font;
	};
}
