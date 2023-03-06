#pragma once

#include <vector>
#include <functional>

class SquareCollider;
class CircleCollider;

enum ColliderShape { SQUARE, CIRCLE };

class Collider
{
public:

	Collider(float x, float y, ColliderShape shape, std::function<void()> collisionEvent);
	~Collider();

	void CheckCollision(std::vector<Collider*> colliders);

	void SetX(float x);
	void SetY(float y);
	float GetX();
	float GetY();
	ColliderShape GetShape();

protected:
	void OnCollision();
	bool IsCollided(Collider* collider);

	virtual bool SquareCheck(SquareCollider* collider) = 0;
	virtual bool CircleCheck(CircleCollider* collider) = 0;

	float m_position[2] = { 0,0 };
	ColliderShape m_shape;
	std::function<void()> m_collision_event;

};