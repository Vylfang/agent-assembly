#ifndef CBULLET_H
#define CBULLET_H

#include "ctexture.h"


class CBullet
{
public:
    CBullet();
    CBullet(int orientation, int startposx, int startposy);
    void IsMoving(int scene_width);
    bool GetIsAlive();
    void SetIsAlive(int orientation, int startposx, int startposy);
    void SetAlive(bool aliveset);
    void Render(SDL_Renderer* gRenderer);
    void Free();
    void SetTexture(CTexture *newtexture);
    void SetIsDead();
    ~CBullet();
    SDL_Rect GetRect();

private:
    int m_posx;
    int m_posy;
    int m_vel;
    int m_dx;
    bool m_isalive;
    CTexture *m_bullettexture;
    SDL_Rect m_hitbox;
};

#endif // CBULLET_H
