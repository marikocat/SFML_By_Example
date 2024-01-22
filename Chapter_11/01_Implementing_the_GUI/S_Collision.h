#pragma once

#include "S_Base.h"

struct TileInfo;
class Map;

struct CollisionElement
{
	CollisionElement(float l_area, TileInfo* l_info, const sf::FloatRect& l_bounds)
		: m_area(l_area), m_tile(l_info), m_tileBounds(l_bounds) {}

	float m_area;
	TileInfo* m_tile;
	sf::FloatRect m_tileBounds;
};

using Collisions = std::vector<CollisionElement>;

class S_Collision : public S_Base
{
public:
	S_Collision(SystemManager* l_systemMgr);
	~S_Collision();

	void SetMap(Map* l_map);

	void Update(float l_dT) override;
	void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event) override;
	void Notify(const Message& l_message) override;
private:
	// Method to process entity-on entity intersection tests.
	void EntityCollisions();

	// The tile-on-entity collision test.
	void MapCollisions(const EntityId& l_entity, C_Position* l_pos, C_Collidable* l_col);

	// The entity is checked for being outside the boundaries of our map.
	void CheckOutOfBounds(C_Position* l_pos, C_Collidable* l_col);

	Map* m_gameMap;
};