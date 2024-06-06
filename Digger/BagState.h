#pragma once
#include "BagComponent.h"
#include "TransformComponent.h"

class NeutralState;
class ShakingState;
class FallingState;
class BrokenState;

class BagState
{
public:
	BagState(BagComponent* pBag) {};
	virtual ~BagState();
	//virtual void HandleInput()


	virtual void Update(float deltaTime) = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	bool CanBePushed()const { return m_CanBePushed; };



	//states
	static NeutralState neutral;
	static ShakingState shaking;
	static FallingState falling;
	static BrokenState broken;

protected:
	BagComponent* m_pBag{};
	bool m_CanBePushed{true};
};


class NeutralState final : public BagState
{
public:
	NeutralState(BagComponent* pBag);
	virtual ~NeutralState() override = default;

	virtual void Update(float deltaTime) override;
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
	const float m_ShakeTimerMax{ 2.f };
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
	dae::TransformComponent* pOwnerTransform;
};

class BrokenState final : public BagState
{
public:
	BrokenState(BagComponent* pBag);
	virtual ~BrokenState() override = default;

	virtual void Update(float deltaTime) override;
	virtual void OnEnter() override;
	virtual void OnExit() override;

private:
	dae::TransformComponent* pOwnerTransform;
};

