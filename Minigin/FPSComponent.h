#pragma once

#include "Component.h"
#include "TextComponent.h"
namespace dae
{
	class FPSComponent final : public Component //TODO: Calculate average, no time so far
	{
	public:
		FPSComponent(GameObject* pOwner);
		~FPSComponent() override;
		void Update(float deltaTime) override;
		int GetFPS() const;

	private:
		int m_FPS;
		float m_timer;
		TextComponent* m_pOwnersTextComponent{};
	};
}
