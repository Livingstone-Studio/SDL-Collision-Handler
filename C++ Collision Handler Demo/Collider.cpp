#include "Collider.h"

#include "SquareCollider.h"
#include "CircleCollider.h"

Collider::Collider(float x, float y, ColliderShape shape, std::function<void()> collisionEvent)
	: m_position{ x,y }, m_shape{ shape }, m_collision_event{ collisionEvent }
{
}

Collider::~Collider()
{
}

void Collider::CheckCollision(std::vector<Collider*> colliders)
{
	for (Collider* collider : colliders)
	{
		if (collider && collider != this) 
		{
			if (IsCollided(collider))
			{
				OnCollision();
			}
		}
	}
}

void Collider::SetX(float x)
{
	m_position[0] = x;
}

void Collider::SetY(float y)
{
	m_position[1] = y;
}

float Collider::GetX()
{
	return m_position[0];
}

float Collider::GetY()
{
	return m_position[1];
}

ColliderShape Collider::GetShape()
{
	return m_shape;
}

void Collider::OnCollision()
{
	if (m_collision_event) m_collision_event();
}

bool Collider::IsCollided(Collider* collider)
{
	switch (collider->GetShape())
	{
	case SQUARE:
		return SquareCheck(dynamic_cast<SquareCollider*>(collider));
		break;
	case CIRCLE:
		return CircleCheck(dynamic_cast<CircleCollider*>(collider));
		break;
	}

	return false;
}
