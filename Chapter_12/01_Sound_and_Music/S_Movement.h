#pragma once

#include "S_Base.h"

enum class Axis{x, y};

class Map;
class S_Movement : public S_Base
{
public:
	S_Movement(SystemManager* l_systemMgr);
	~S_Movement();

	void Update(float l_dT) override;
	void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event) override;
	void Notify(const Message& l_message) override;

	void SetMap(Map* l_gameMap);
private:
	void StopEntity(const EntityId& l_entity, const Axis& l_axis);
	void SetDirection(const EntityId& l_entity, const Direction& l_dir);
	const sf::Vector2f& GetTileFriction(unsigned int l_elevation,
		unsigned int l_x, unsigned int l_y);
	void MovementStep(float l_dT, C_Movable* l_movable, C_Position* l_position);

	Map* m_gameMap;
};