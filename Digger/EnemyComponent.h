#pragma once
#include "Component.h"
#include "TextureComponent.h"
#include <random>
#include <map>



//NOBBIN IS SLOWER
//HOBBIN IS FASTER

class GridMoveCommand;
class MapRegistryComponent;
enum facingDirection //ENEMY is in the enums to not shadow or confuse another enum thats similar
{
	ENEMYLEFT,
	ENEMYRIGHT,
	ENEMYUP,
	ENEMYDOWN
};
class EnemyComponent : public dae::Component
{
public:
	EnemyComponent(dae::GameObject* pOwner, bool startsAsHobbin = false);
	~EnemyComponent() override;

	void Update(float deltaTime) override;
	void FixedUpdate() override;
	bool GetIsTransformed()const { return m_IsTransformed; };

	EnemyComponent(const EnemyComponent& other) = delete;
	EnemyComponent(EnemyComponent&& other) = delete;
	EnemyComponent& operator=(const EnemyComponent& other) = delete;
	EnemyComponent& operator=(EnemyComponent&& other) = delete;

	bool GetIsPlayerControlled()const { return m_playerControlled; };

private:
	MapRegistryComponent* m_pMapRegister{};
	dae::TransformComponent* m_pOwnerTransform{};
	facingDirection m_DirectionGoing{facingDirection::ENEMYDOWN};
	facingDirection m_DirectionCameFrom{facingDirection::ENEMYUP};//starts as up by default

	//nobbins v hobbins stuff
	std::shared_ptr<dae::Texture2D> m_pHobbinTexture{};//init in m_InitTextures
	std::shared_ptr<dae::Texture2D> m_pNobbinTexture{};//init in m_InitTextures
	const float m_NobbinsMoveSpeed{100.f};
	const float m_HobbinsMoveSpeed{150.f};

	//transformation
	const float m_TransformTimerMax{ 15.f };
	float m_TransformTimerCurrent{ 0.f };
	bool m_IsTransformed{ false };
	void m_Transform();

	//location
	glm::vec2 m_lastGridPos{-100.f,-100.f}; //set negative so update goes by itself.

	//could be a general commands map, but then I need to static cast in transform. for now only movement is needed so keeping it at GridMoveComms
	std::map<facingDirection, std::unique_ptr<GridMoveCommand>> m_moveCommandsMap{};

	void m_SetDirection(facingDirection toSet);

	//direction helpers
	facingDirection m_GetOppositeDirection(facingDirection input);
	bool m_NavigationCheck(float x, float y)const;
	std::random_device m_randomDevice{};

	void m_UpdateFacingDirection();
	void m_InitTextures();
	void m_InitCommands();

	void m_InitP2Commands();

	bool m_playerControlled{ false };
};

