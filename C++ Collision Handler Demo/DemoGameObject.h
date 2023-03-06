#pragma once

#include "SDL.h"

class Collider;

class DemoGameObject
{
public:
	DemoGameObject(SDL_Rect t, float moveX, float moveY, Collider* collider);
	~DemoGameObject();

	void Draw(SDL_Renderer* renderer);
	void Move();
	void ChangeDirection();

	Collider* GetCollider();

private:

	Collider* m_collider;
	SDL_Rect m_transform;
	float m_frame_movement[2];

};

