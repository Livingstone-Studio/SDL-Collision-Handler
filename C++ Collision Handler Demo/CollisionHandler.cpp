#include "CollisionHandler.h"

#include <iostream>

std::vector<Collider*> CollisionHandler::m_colliders{ nullptr };

void CollisionHandler::Add(Collider* collider)
{
	m_colliders.push_back(collider);
}

void CollisionHandler::Remove(Collider* collider)
{
	m_colliders.erase(std::remove(m_colliders.begin(), m_colliders.end(), collider), m_colliders.end());
}

void CollisionHandler::Update()
{
	for (Collider* collider : m_colliders) 
	{
		if (collider)
		{
			collider->CheckCollision(m_colliders);
		}
	}
}

void CollisionHandler::Cleanup()
{
	for (Collider* collider : m_colliders)
	{
		if (collider)
		{
			delete collider;
		}
	}

	m_colliders.clear();
}
