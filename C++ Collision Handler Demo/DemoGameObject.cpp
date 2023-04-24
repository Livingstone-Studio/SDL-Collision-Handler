#include "DemoGameObject.h"

#include "RectangleCollider.h"
#include "CircleCollider.h"

DemoGameObject::DemoGameObject(SDL_Rect t, float moveX, float moveY, Collider::ColliderShape shape)
	: m_transform{t}, m_frame_movement{moveX,moveY}
{
    switch (shape) 
    {
    case Collider::RECT:
        m_collider = new RectangleCollider(t.x, t.y, t.w, t.h, nullptr);
        break;
    case Collider::CIRCLE:
        m_collider = new CircleCollider(t.x, t.y, t.w, nullptr);
        break;
    }


    if ((moveX != 0 || moveY != 0) && m_collider)
    {
        m_collider->SetCollisionEvent(std::bind(&DemoGameObject::ChangeDirection, this));
    }
}

DemoGameObject::~DemoGameObject()
{
	if (m_collider) delete m_collider;
}

void DemoGameObject::Draw(SDL_Renderer* renderer)
{
    switch (m_collider->GetShape())
    {
    case Collider::RECT:
        DrawRectangle(renderer);
        break;
    case Collider::CIRCLE:
        DrawCircle(renderer);
        break;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

Collider* DemoGameObject::GetCollider()
{
	return m_collider;
}

void DemoGameObject::DrawRectangle(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    RectangleCollider* box = dynamic_cast<RectangleCollider*>(m_collider);
    if (box)
    {
        SDL_Rect dimensions = { box->GetX() - box->GetW() / 2, box->GetY() - box->GetH() / 2, box->GetW(), box->GetH() };
        SDL_RenderDrawRect(renderer, &dimensions);
    }
}

void DemoGameObject::DrawCircle(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    CircleCollider* circle = dynamic_cast<CircleCollider*>(m_collider);
    if (circle)
    {
        int x = 0;
        int y = circle->GetRadius();
        int d = 3 - 2 * circle->GetRadius();
        while (y >= x) {
            SDL_RenderDrawPoint(renderer, circle->GetX() + x, circle->GetY() + y);
            SDL_RenderDrawPoint(renderer, circle->GetX() + y, circle->GetY() + x);
            SDL_RenderDrawPoint(renderer, circle->GetX() - x, circle->GetY() + y);
            SDL_RenderDrawPoint(renderer, circle->GetX() - y, circle->GetY() + x);
            SDL_RenderDrawPoint(renderer, circle->GetX() + x, circle->GetY() - y);
            SDL_RenderDrawPoint(renderer, circle->GetX() + y, circle->GetY() - x);
            SDL_RenderDrawPoint(renderer, circle->GetX() - x, circle->GetY() - y);
            SDL_RenderDrawPoint(renderer, circle->GetX() - y, circle->GetY() - x);
            if (d < 0) {
                d += 4 * x + 6;
            }
            else {
                d += 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }
}

void DemoGameObject::ChangeDirection()
{
	m_frame_movement[0] *= -1;
	m_frame_movement[1] *= -1;
}

void DemoGameObject::Move()
{
	m_transform.x += m_frame_movement[0];
	m_transform.y += m_frame_movement[1];

	m_collider->SetX(m_transform.x);
	m_collider->SetY(m_transform.y);
}
