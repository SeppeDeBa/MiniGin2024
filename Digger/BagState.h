#pragma once

#include "TransformComponent.h"


class BagComponent;

class BagState //spoke to a similar implementation with Finnean of my class, he uses constructor and destructor which I'm not a super fan of.
{
public:
	BagState(BagComponent* pBag);
	virtual ~BagState() = default;
	//virtual void HandleInput()

	virtual void Update(float) = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;


protected:
	BagComponent* m_pBag{};
};


class NeutralState final : public BagState
{
public:
	NeutralState(BagComponent* pBag);
	virtual ~NeutralState() override = default;

	virtual void Update(float) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
};

class ShakingState final : public BagState
{
public:
	ShakingState(BagComponent* pBag);
	virtual ~ShakingState() override = default;

	virtual void Update(float deltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;

private:
	const float m_ShakeTimerMax{ 3.f };
	const int m_JigglesPerSec{ 8 };
	float m_ShakeTimer{ 0.f };
private:
	void UpdateVisuals();
};


class FallingState final : public BagState
{
public:
	FallingState(BagComponent* pBag);
	virtual ~FallingState() override = default;

	virtual void Update(float deltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;

private:
	dae::TransformComponent* m_pOwnerTransform;
	const float m_FallingSpeed{5.f};
};

class BrokenState final : public BagState
{
public:
	BrokenState(BagComponent* pBag);
	virtual ~BrokenState() override = default;

	virtual void Update(float) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;

private:
	dae::TransformComponent* m_pOwnerTransform;
};

