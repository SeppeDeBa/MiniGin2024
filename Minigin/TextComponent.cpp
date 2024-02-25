#include <stdexcept>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "TextureComponent.h"

dae::TextComponent::TextComponent(GameObject* pOwner, const std::string& stringText, std::shared_ptr<Font> font)
	:Component(pOwner)
	, m_font( std::move(font) )
	, m_textString(stringText)
	, m_needsUpdate(true)
{

}

void dae::TextComponent::Update(float) //used from TextObject given in base MiniGin
{
	if(m_needsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_textString.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		GetGameObject()->GetComponent<dae::TextureComponent>()->SetTexture(std::make_shared<Texture2D>(texture));
		m_needsUpdate = false;
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_textString = text;
	m_needsUpdate = true;


}



