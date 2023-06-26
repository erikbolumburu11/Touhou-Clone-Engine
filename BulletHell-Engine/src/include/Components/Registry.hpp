#pragma once 
#include <unordered_map>
#include "Components/Components.hpp"

using Entity = std::size_t;

struct Registry {
	std::unordered_map<Entity, SpriteComponent> sprites;
	std::unordered_map<Entity, TransformComponent> transforms;
	std::unordered_map<Entity, NameComponent> names;
	std::unordered_map<Entity, VelocityComponent> velocities;
	std::unordered_map<Entity, PlayerMovementComponent> playerMovements;
	std::unordered_map<Entity, BulletEmitterComponent> bulletEmitters;
	std::unordered_map<Entity, BulletComponent> bullets;
};