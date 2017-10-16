#include "cbullet.h"

CBullet::CBullet()
{
    m_posx = 0;
    m_posy = 0;
    m_vel = 8;
    m_dx = 0;
    m_hitbox.x = 0;
    m_hitbox.y = 0;
    m_hitbox.h = 2;
    m_hitbox.w = 3;
    m_isalive = false;
}

CBullet::CBullet(int orientation, int startposx, int startposy)
{
    m_posx = startposx;
    m_posy = startposy;
    if (orientation){m_dx=m_vel;}
    else {m_dx=-m_vel;}
}

CBullet::~CBullet()
{
this->Free();
}

void CBullet::IsMoving(int scene_width)
{
    //Move the dot left or right
    m_posx += m_dx;
    m_hitbox.x = m_posx;
    //If the dot went too far to the left or right
    if( ( m_posx < 0 ) || ( (m_posx + m_bullettexture->GetWidth()) > scene_width ) )
    {
        //Move back
        m_posx -= m_dx;
        m_hitbox.x = m_posx;
        this->SetIsDead();
        //this->m_isalive = false;
    }
}

void CBullet::Render(SDL_Renderer* gRenderer)
{
m_bullettexture->Render(m_posx,m_posy,NULL,gRenderer,SDL_FLIP_NONE);
}

void CBullet::Free()
{
   m_bullettexture->Free();
}

void CBullet::SetTexture(CTexture *newtexture)
{
m_bullettexture = newtexture;
}

bool CBullet::GetIsAlive()
{
    return m_isalive;
}

void CBullet::SetIsAlive(int orientation, int startposx, int startposy)
{
    m_isalive = true;


    m_posy = startposy+33;
    m_hitbox.y = startposy+33;
    if(orientation){m_dx=m_vel;m_posx = startposx+76;}else{m_dx=-m_vel;m_posx = startposx-6;}
m_hitbox.x = m_posx;
}

void CBullet::SetAlive(bool aliveset)
{
    m_isalive = aliveset;
}

SDL_Rect CBullet::GetRect()
{
return m_hitbox;
}

void CBullet::SetIsDead()
{
    m_isalive = false;
    m_posy = 0;
    m_posx = 0;
    m_hitbox.x = m_posx;
    m_hitbox.y = m_posy;
    m_dx = 0;
}
