#pragma once

#include "SquareCollider.h"
#include "CircleCollider.h"

#include <vector>

class CollisionHandler
{
public:
	static void Add(Collider* collider);
	static void Remove(Collider* collider);

	static void Update();
	static void Cleanup();

private:
	static std::vector<Collider*> m_colliders;

};