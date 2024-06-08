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

	//BagState* GetBagState() const { return m_pBagState.get(); };


	bool CanPush() const { return m_canBePushed; };
	bool CanKill() const { return m_canKill; };
	bool CanCollect() const { return m_canBeCollected; };


	int lastStableRow{};

	void MakePushable() { m_canKill = false; m_canBeCollected = false; m_canBePushed = true; };
	void MakeKilling() { m_canKill = true; m_canBeCollected = false; m_canBePushed = false; };
	void MakeCollectable() { m_canKill = false; m_canBeCollected = true; m_canBePushed = false; };
	void MakeUninteractable() { m_canKill = false; m_canBeCollected = false; m_canBePushed = false; };
	//virtual void HandleInput(Input)
private:
	void InitBagTextures();
	std::map<BagRotation, std::shared_ptr<dae::Texture2D>> m_pTexturesMap{};
	BagRotation m_CurrentRotation;
	std::unique_ptr<BagState> m_pBagState;

	bool m_canKill{false};
	bool m_canBeCollected{false};
	bool m_canBePushed{ true };

};

