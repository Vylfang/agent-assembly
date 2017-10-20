#include "ccharacter.h"

CCharacter::CCharacter()
{
    m_alive = 1;
    m_x = 0;
    m_y = 0;
    m_dx = 0;
    m_dy = 0;
    m_visible = 1;
    m_orientation = 1;
    m_hitbox.h = 66;//80;
    m_hitbox.w = 20;//70;
    m_hitbox.x = m_x+22;
    m_hitbox.y = m_y+7;
    m_stabhitbox.h = 15;//80;
    m_stabhitbox.w = 20;//70;
    m_stabhitbox.x = m_x+50;//or flipped (m_x+1)
    m_stabhitbox.y = m_y+36;//or flipped ()
}

CCharacter::~CCharacter()
{
}

bool CCharacter::GetAlive()
{
    return m_alive;
}

void CCharacter::SetVelocity(int dx, int dy)
{
m_dx = dx;
m_dy = dy;
}

void CCharacter::SetPosition(int x, int y)
{
    m_x = x;
    if(this->GetOrientation())
    {
    m_stabhitbox.x = m_x+50;
    m_hitbox.x = m_x+22;
    }
    else
    {
    m_stabhitbox.x = m_x+1;
    m_hitbox.x = m_x+28;
    }
    m_y = y;
    m_hitbox.y = m_y+7;
    m_stabhitbox.y = m_y+36;
}

void CCharacter::SetAlive(bool alive)
{
 m_alive = alive;
}

void CCharacter::IsMoving(int scene_width,int scene_height)
{
    //Move the dot left or right
    m_x += m_dx;

    if(this->GetOrientation())
    {
    m_stabhitbox.x = m_x+50;
    m_hitbox.x = m_x+22;
    }
    else
    {
    m_stabhitbox.x = m_x+1;
        m_hitbox.x = m_x+28;
    }




    //If the dot went too far to the left or right
    if( ( m_x < 0 ) || ( (m_x + 70) > scene_width ) )
    {
        //Move back
        m_x -= m_dx;

        if(this->GetOrientation())
        {
        m_stabhitbox.x = m_x+50;
        m_hitbox.x = m_x+22;
        }
        else
        {
        m_stabhitbox.x = m_x+1;
            m_hitbox.x = m_x+28;
        }
    }

    //Move the dot up or down
    m_y += m_dy;
    m_hitbox.y = m_y+7;
    m_stabhitbox.y = m_y+36;//or flipped ()
    //If the dot went too far up or down
    if( ( m_y < 0 ) || ( (m_y + 80) > scene_height ) )
    {
        //Move back
        m_y -= m_dy;
        m_hitbox.y = m_y+7;
        m_stabhitbox.y = m_y+36;//or flipped ()
    }

}

void CCharacter::Render(SDL_Rect* clip, SDL_Renderer* gRenderer)
{
  if(m_orientation){m_chartexture->Render( m_x, m_y, clip, gRenderer, SDL_FLIP_NONE);}
  else{m_chartexture->Render( m_x, m_y, clip, gRenderer, SDL_FLIP_HORIZONTAL);}
}

void CCharacter::SetTexture(CTexture *chartexture)
{
  m_chartexture = chartexture;
}

int CCharacter::GetVelocity()
{
    return (m_dx*m_dx+m_dy*m_dy);
}

void CCharacter::Free()
{
   m_alive = 0;
   m_x = 0;
   m_y = 0;
   m_dx = 0;
   m_dy = 0;
   m_chartexture= NULL;

}


void CCharacter::SetVisible(bool trigger)
{
    m_visible = trigger;
}

bool CCharacter::GetVisible()
{
return m_visible;
}

bool CCharacter::GetOrientation()
{
    return m_orientation;
}

void CCharacter::SetOrientation(bool neworientation)
{
    m_orientation = neworientation;
}

/*
void CCharacter::SetRect(SDL_Rect grect)
{
    m_hitbox = grect;
}
*/

SDL_Rect CCharacter::GetRect()
{
return m_hitbox;
}

int CCharacter::GetPosX()
{
    return m_x;
}

int CCharacter::GetPosY()
{
    return m_y;
}

SDL_Rect CCharacter::GetStabRect()
{
return m_stabhitbox;
}


