#pragma once
#include <map>
#include "BagState.h"
#include "Component.h"

class BagState;

enum BagRotation
{
	LEFT,
	NEUTRAL,
	RIGHT,
	OPEN
};

class BagComponent : public dae::Component
{
public:
	BagComponent(dae::GameObject* pOwner);
	~BagComponent() override = default;

	void SetTextureByRotation(const BagRotation rotation);

	void Update(float deltaT) override;
	void Render() const override;
	void FixedUpdate() override;

	void SetBagState(std::unique_ptr<BagState> pBagStateToSet);

	int lastStableRow{};
	//virtual void HandleInput(Input)
private:
	void InitBagTextures();
	std::map<BagRotation, std::shared_ptr<dae::Texture2D>> m_pTexturesMap{};
	BagRotation m_CurrentRotation;
	std::unique_ptr<BagState> m_pBagState;
	
};

