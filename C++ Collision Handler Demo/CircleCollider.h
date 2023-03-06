#pragma once

#include "Collider.h"

class CircleCollider : public Collider
{
public:
	CircleCollider(float x, float y, float r, std::function<void()> collisionEvent);
	~CircleCollider();

	float GetRadius();

protected:
	virtual bool SquareCheck(SquareCollider* collider) override;
	virtual bool CircleCheck(CircleCollider* collider) override;

	float GetMagnitude(float x, float y);

	float m_radius;
};

