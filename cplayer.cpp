#include "cplayer.h"

CPlayer::CPlayer()
{
    m_tempdx = 0;
    m_tempdy = 0;
    m_isstabbing = 0;
    m_isfiring = 0;
    m_ammunition = 0;
}

CPlayer::~CPlayer()
{
    m_playercharacter.Free();
}

int CPlayer::GetBind(int number)
{

    int keybind = 0;
/*
    switch(number)
{
case 0 : keybind = m_keybindup; break;
case 1 : keybind = m_keybinddown; break;
case 2 : keybind = m_keybindleft; break;
case 3 : keybind = m_keybindright; break;
case 4 : keybind = m_keybindfire; break;
case 5 : keybind = m_keybindstab; break;
case 6 : keybind = m_keybindspecial; break;
}
*/
return(keybind);
}

void CPlayer::SetBind(int bindnumber, int keybind)
{
    switch(bindnumber)
{
case 0 : m_keybindup = keybind; break;
case 1 : m_keybinddown =keybind ; break;
case 2 :  m_keybindleft =keybind; break;
case 3 :  m_keybindright =keybind; break;
case 4 : m_keybindfire =keybind ; break;
case 5 : m_keybindstab =keybind ; break;
case 6 : m_keybindspecial = keybind ; break;
}
}


 void CPlayer::HandleEvents(SDL_Event& e)
 {

     if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
     {
         if(e.key.keysym.sym == m_keybindstab){m_isstabbing =1;}
         if(e.key.keysym.sym == m_keybindfire){m_isfiring = 1;}
         if(e.key.keysym.sym == m_keybinddown){m_tempdy+=1;}
         if(e.key.keysym.sym == m_keybindup){m_tempdy-=1;}
         if(e.key.keysym.sym == m_keybindleft){m_tempdx-=1;m_playercharacter.SetOrientation(0);}
         if(e.key.keysym.sym == m_keybindright){m_tempdx+=1;m_playercharacter.SetOrientation(1);}
     }
     else if(e.type == SDL_KEYUP && e.key.repeat == 0)
     {
         if(e.key.keysym.sym == m_keybindstab){m_isstabbing = 0;}
         if(e.key.keysym.sym == m_keybindfire){m_isfiring = 0;}
         if(e.key.keysym.sym == m_keybinddown){m_tempdy-=1;}
         if(e.key.keysym.sym == m_keybindup){m_tempdy+=1;}
         if(e.key.keysym.sym == m_keybindleft){m_tempdx+=1;}
         if(e.key.keysym.sym == m_keybindright){m_tempdx-=1;}

     }
 }

 void CPlayer::IsMoving(int screenwidth, int screenheigth)
 {
m_playercharacter.SetVelocity(m_tempdx,m_tempdy);
m_playercharacter.IsMoving(screenwidth,screenheigth);

 }

 bool CPlayer::GetStabbing()
{

return m_isstabbing;

 }

 void CPlayer::SetStabbing(bool newstab)
 {
     m_isstabbing = newstab;
 }

 bool CPlayer::GetFiring()
{

return m_isfiring;

 }


void CPlayer::SetFiring(bool newfire)
{

m_isfiring = newfire;

 }

int CPlayer::GetAmmunition()
{
    return(m_ammunition);
}

void CPlayer::DepleteAmmunition()
{
    m_ammunition -= 1;
}

void CPlayer::SetAmmunition(int ammunition)
{
    m_ammunition = ammunition;
}
