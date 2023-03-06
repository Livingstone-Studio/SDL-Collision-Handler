#include "DemoGameObject.h"

#include "Collider.h"
#include "CircleCollider.h"

DemoGameObject::DemoGameObject(SDL_Rect t, float moveX, float moveY, Collider* collider)
	: m_transform{t}, m_frame_movement{moveX,moveY}, m_collider{collider}
{
}

DemoGameObject::~DemoGameObject()
{
	if (m_collider) delete m_collider;
}

void DemoGameObject::Draw(SDL_Renderer* renderer)
{
    if (m_collider->GetShape() == SQUARE)
    {
        SDL_Surface* Surface = SDL_CreateRGBSurface(0, m_transform.w, m_transform.h, 32, 0, 0, 0, 0);
        Uint32 blockColour = SDL_MapRGB(Surface->format, 255, 255, 255);
        SDL_FillRect(Surface, NULL, blockColour);

        SDL_Texture* Texture = SDL_CreateTextureFromSurface(renderer, Surface);

        SDL_FreeSurface(Surface);

        SDL_Rect destRect = { m_transform.x-m_transform.w/2, m_transform.y - m_transform.h / 2, m_transform.w, m_transform.h };
        SDL_RenderCopy(renderer, Texture, NULL, &destRect);

        SDL_DestroyTexture(Texture);
    }
    else
    {
        //Changes the colour of the draw so that the circle is visual against the background
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        CircleCollider* c = dynamic_cast<CircleCollider*>(m_collider);

        if (c) 
        {

            int offsetx = 0;
            int offsety = c->GetRadius();
            int d = c->GetRadius() - 1;
            int status = 0;

            while (offsety >= offsetx) {

                status += SDL_RenderDrawLine(renderer, m_transform.x - offsety, m_transform.y + offsetx, m_transform.x + offsety, m_transform.y + offsetx);
                status += SDL_RenderDrawLine(renderer, m_transform.x - offsetx, m_transform.y + offsety, m_transform.x + offsetx, m_transform.y + offsety);
                status += SDL_RenderDrawLine(renderer, m_transform.x - offsetx, m_transform.y - offsety, m_transform.x + offsetx, m_transform.y - offsety);
                status += SDL_RenderDrawLine(renderer, m_transform.x - offsety, m_transform.y - offsetx, m_transform.x + offsety, m_transform.y - offsetx);

                if (status < 0)
                {
                    status = -1;
                    break;
                }

                if (d >= 2 * offsetx)
                {
                    d -= 2 * offsetx + 1;
                    offsetx += 1;
                }
                else if (d < 2 * (c->GetRadius() - offsety))
                {
                    d += 2 * offsety - 1;
                    offsety -= 1;
                }
                else
                {
                    d += 2 * (offsety - offsetx - 1);
                    offsety -= 1;
                    offsetx += 1;
                }
            }

        }

        //Changes the draw colour back to the background colour 
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    }
}

Collider* DemoGameObject::GetCollider()
{
	return m_collider;
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
