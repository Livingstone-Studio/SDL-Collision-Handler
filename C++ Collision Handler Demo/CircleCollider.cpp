#include "CircleCollider.h"
#include "SquareCollider.h"

#include <iostream>

CircleCollider::CircleCollider(float x, float y, float r, std::function<void()> collisionEvent)
    : Collider(x,y,CIRCLE,collisionEvent), m_radius{ r }
{
}

CircleCollider::~CircleCollider()
{
}

float CircleCollider::GetRadius()
{
    return m_radius;
}

bool CircleCollider::SquareCheck(SquareCollider* collider)
{
    if (!collider) return false;

    float o_pos[2] = { collider->GetX(), collider->GetY() };
    float o_size[2] = { collider->GetW(), collider->GetH() };

    float axis_distance[2] = { abs(m_position[0] - o_pos[0]),abs(m_position[1] - o_pos[1]) };

    if (axis_distance[0] > (o_size[0] / 2 + m_radius)) { return false; }
    if (axis_distance[1] > (o_size[1] / 2 + m_radius)) { return false; }

    if (axis_distance[0] <= (o_size[0] / 2)) { return true; }
    if (axis_distance[1] <= (o_size[1] / 2)) { return true; }

    return false;
}

bool CircleCollider::CircleCheck(CircleCollider* collider)
{
    if (!collider) return false;

    float o_x, o_y, o_radius;

    o_x = collider->GetX();
    o_y = collider->GetY();
    o_radius = collider->GetRadius();

    float direction[2] = { o_x - m_position[0], o_y - m_position[1] };

    float distance = GetMagnitude(direction[0],direction[1]);

    if (distance <= m_radius + o_radius)
    {
        return true;
    }

    return false;
}

float CircleCollider::GetMagnitude(float x, float y)
{
    float i = (x * x) + (y * y);

    if (i == 0) return 0;
    else return sqrt(i);
}
