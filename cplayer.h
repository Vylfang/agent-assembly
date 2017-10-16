#ifndef CPLAYER_H
#define CPLAYER_H

#include <ccharacter.h>

class CPlayer
{
public:
    CPlayer();
    ~CPlayer();
    void HandleEvents(SDL_Event& e);
    int GetBind(int number);
    void SetBind(int bindnumber, int keybind);
  //  void ChangeKeySetting(int keytoswitch, SDL_Event& e);
  //  void FakeDead();
    void IsMoving(int screenwidth, int screenheigth);
    void LinkCharacter(CCharacter* linkedcharacter);
    bool GetStabbing();
    void SetStabbing(bool newstab);
    bool GetFiring();
    void SetFiring(bool newstab);
    int GetAmmunition();
    void DepleteAmmunition();
    void SetAmmunition(int ammunition);


        CCharacter m_playercharacter;
private:

    int m_keybinddown = SDLK_DOWN;
    int m_keybindup = SDLK_UP;
    int m_keybindleft = SDLK_LEFT;
    int m_keybindright = SDLK_RIGHT;
    int m_keybindfire = SDLK_KP_1;
    int m_keybindstab = SDLK_KP_2;
    int m_keybindspecial = SDLK_KP_3;

    int m_tempdx;
    int m_tempdy;
    bool m_isstabbing;
    bool m_isfiring;
    int m_ammunition;
};

#endif // CPLAYER_H
