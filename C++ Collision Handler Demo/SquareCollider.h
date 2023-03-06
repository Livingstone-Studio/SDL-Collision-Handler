#pragma once

#include "Collider.h"

class SquareCollider : public Collider
{
public:
	SquareCollider(float x, float y, float w, float h, std::function<void()> collisionEvent);
	~SquareCollider();

	float GetW();
	float GetH();

protected:
	virtual bool SquareCheck(SquareCollider* collider) override;
	virtual bool CircleCheck(CircleCollider* collider) override;

	float m_size[2];
};

