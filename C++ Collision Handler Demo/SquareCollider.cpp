#include "SquareCollider.h"
#include "CircleCollider.h"

#include <iostream>

SquareCollider::SquareCollider(float x, float y, float w, float h, std::function<void()> collisionEvent)
    : Collider(x,y,SQUARE,collisionEvent),m_size{ w,h }
{
}

SquareCollider::~SquareCollider()
{
}

float SquareCollider::GetW()
{
    return m_size[0];
}

float SquareCollider::GetH()
{
    return m_size[1];
}

bool SquareCollider::SquareCheck(SquareCollider* collider)
{
    if (!collider) return false;

	float o_pos[2] = { collider->GetX(), collider->GetY() };
	float o_size[2] = { collider->GetW()/2, collider->GetH()/2 };

	float m_c1_min[2] = { m_position[0] - m_size[0]/2, m_position[1] - m_size[1]/2 };
	float m_c1_max[2] = { m_position[0] + m_size[0]/2, m_position[1] + m_size[1]/2 };

	float m_c2_min[2] = { o_pos[0] - o_size[0], o_pos[1] - o_size[1] };
	float m_c2_max[2] = { o_pos[0] + o_size[0], o_pos[1] + o_size[1] };


	if (m_c1_min[0] > m_c2_max[0] || m_c1_max[0] < m_c2_min[0]) return false;
	if (m_c1_min[1] > m_c2_max[1] || m_c1_max[1] < m_c2_min[1]) return false;

	return true;
}

bool SquareCollider::CircleCheck(CircleCollider* collider)
{
    if (!collider) return false;

    float o_pos[2] = { collider->GetX(), collider->GetY() };

    float axis_distance[2] = { abs(m_position[0] - o_pos[0]),abs(m_position[1] - o_pos[1]) };

    if (axis_distance[0] > (m_size[0] / 2 + collider->GetRadius())) { return false; }
    if (axis_distance[1] > (m_size[1] / 2 + collider->GetRadius())) { return false; }

    if (axis_distance[0] <= (m_size[0] / 2)) { return true; }
    if (axis_distance[1] <= (m_size[1] / 2)) { return true; }

    return false;
}
