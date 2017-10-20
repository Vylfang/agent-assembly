#ifndef CCHARACTER_H
#define CCHARACTER_H

#include "ctexture.h"


class CCharacter
{
public:
    CCharacter();
    ~CCharacter();
    bool GetAlive();
    void IsMoving(int scene_width,int scene_height);
    void SetTexture(CTexture *chartexture);
    void SetVelocity(int dx, int dy);
    void SetAlive(bool alive);
    void SetPosition(int x, int y);
    int GetVelocity();
    void Render(SDL_Rect* clip, SDL_Renderer* gRenderer);
    void Free();
    void SetVisible(bool trigger);


    bool GetVisible();
    bool GetOrientation();
    void SetOrientation(bool neworientation);
    SDL_Rect GetRect();


    int GetPosX();
    int GetPosY();

    SDL_Rect GetStabRect();
    //void SetRect(SDL_Rect grect);
    //int IsShooting();
    //int IsStabbing();


private:
    bool m_alive;
    int m_x;
    int m_y;
    int m_dx;
    int m_dy;
    CTexture *m_chartexture;
    int m_visible;
    bool m_orientation;
    SDL_Rect m_hitbox;
    SDL_Rect m_stabhitbox;
    //SDL_Rect m_hitbox;
    //int m_shots

};
#endif // CCHARACTER_H
