#pragma once
#include <map>

#include "Component.h"

enum BagRotation
{
	LEFT,
	NEUTRAL,
	RIGHT
};

class BagComponent : public dae::Component
{
public:
	BagComponent(dae::GameObject* pOwner);
	~BagComponent() override;

	void SetTextureByRotation(const BagRotation rotation);

	void Update(float) override;
	void Render() const override;
	void FixedUpdate() override;
	
	//virtual void HandleInput(Input)
private:
	void InitBagTextures();
	std::map<BagRotation, std::shared_ptr<dae::Texture2D>> m_pTexturesMap{};
	BagRotation m_CurrentRotation;
};

