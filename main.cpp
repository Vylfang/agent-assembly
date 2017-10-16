//Using SDL, SDL_image, standard IO, and strings
#include <ccharacter.h>
#include <ctexture.h>
#include <cbullet.h>
#include <stdlib.h>
#include <cplayer.h>
#include <sstream>
#include <time.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int SPRITE_WIDTH = 70;
const int SPRITE_HEIGHT = 80;

const int CHARSPEED = 1;
const int SPRITETOTALFRAMES = 13;
const int INICHARNUMBER = 50;
const int ROUNDTIME = 179;
const int STARTAMMUNITION = 3;
const int BULLETBUFFER = 100;
const int PTSIZE = 28;
//The application time based timer


//Starts up SDL and creates window
bool init();
bool checkcollision(SDL_Rect a, SDL_Rect b);
//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
CTexture cchartexture;
CTexture cbackgroundtexture;
CTexture cbullettexture;

CCharacter ccharacter[INICHARNUMBER];
SDL_Rect spriteclips[SPRITETOTALFRAMES];


CPlayer playera;
CPlayer playerb;

CBullet cbullet[BULLETBUFFER];


CTexture playerascoretext;
CTexture playerbscoretext;
CTexture playerabulletstext;
CTexture playerbbulletstext;
CTexture winnertext;
CTexture restartclocktext;

TTF_Font *font = NULL;


bool checkcollision(SDL_Rect a, SDL_Rect b)
{
    if((a.x+a.w)<b.x){return false;}
    if(a.x>(b.x+b.w)){return false;}
    if((a.y+a.h)<(b.y)){return false;}
    if(a.y>(b.y+b.h)){return false;}
    return true;
}

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO)<0){printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );success = false;}
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){printf( "Warning: Linear texture filtering not enabled!" );}

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL ){printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );success = false;}
        else
        {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL ){printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );success = false;}
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) ){printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );success = false;}
            }
        }
    }

    if(TTF_Init() == -1)
    {
        printf("SDL_TTF could not initialize! SDL_TTF Error : %s\n", TTF_GetError()); success = false;
    }
    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load dot texture
    if( !cchartexture.LoadFromFile( "Sprites/CharSpriteSheet.png",gRenderer) ){printf( "Failed to load texture!\n" );success = false;}
    else
    {
        //standing and moving frame number 1
        spriteclips[0].x = 0;
        spriteclips[0].y = 0;
        spriteclips[0].w = 70;
        spriteclips[0].h = 80;
        //move frame number 2
        spriteclips[1].x = 71;
        spriteclips[1].y = 0;
        spriteclips[1].w = 70;
        spriteclips[1].h = 80;
        //move frame number 3 - standing frame
        spriteclips[2].x = 142;
        spriteclips[2].y = 0;
        spriteclips[2].w = 70;
        spriteclips[2].h = 80;
        //move frame number 4
        spriteclips[3].x = 71;
        spriteclips[3].y = 0;
        spriteclips[3].w = 70;
        spriteclips[3].h = 80;


        //knife attack frame number 1
         spriteclips[4].x = 0;
         spriteclips[4].y = 81;
         spriteclips[4].w = 70;
         spriteclips[4].h = 80;
        //knife attack frame number 2 and 3
         spriteclips[5].x = 141;
         spriteclips[5].y = 81;
         spriteclips[5].w = 70;
         spriteclips[5].h = 80;

         spriteclips[6].x = 141;
         spriteclips[6].y = 81;
         spriteclips[6].w = 70;
         spriteclips[6].h = 80;
        //knife attack frame number 4
         spriteclips[7].x = 0;
         spriteclips[7].y = 81;
         spriteclips[7].w = 70;
         spriteclips[7].h = 80;


        //gun attack frame number 1
         spriteclips[8].x = 0;
         spriteclips[8].y = 81;
         spriteclips[8].w = 70;
         spriteclips[8].h = 80;
        //gun attack frame number 2 and 3
         spriteclips[9].x = 71;
         spriteclips[9].y = 81;
         spriteclips[9].w = 70;
         spriteclips[9].h = 80;

         spriteclips[10].x = 71;
         spriteclips[10].y = 81;
         spriteclips[10].w = 70;
         spriteclips[10].h = 80;
        //gun attack frame number 4
         spriteclips[11].x = 0;
         spriteclips[11].y = 81;
         spriteclips[11].w = 70;
         spriteclips[11].h = 80;


         //dead frame number 1 (could be made by rotation)
          spriteclips[12].x = 0;
          spriteclips[12].y = 162;
          spriteclips[12].w = 70;
          spriteclips[12].h = 80;
    }
    if( !cbackgroundtexture.LoadFromFile( "Sprites/backgroundb.png",gRenderer) ){printf( "Failed to load texture!\n" );success = false;}

    if( !cbullettexture.LoadFromFile( "Sprites/bullet.png",gRenderer) ){printf( "Failed to load texture!\n" );success = false;}

    font = TTF_OpenFont("Font/gymkhana-bk.ttf",PTSIZE);
    if(font == NULL){printf("Failed to load font! SDL_TTF error : %s\n",TTF_GetError());success = false;}


    return success;
}

void close()
{
    //Free loaded images
    cchartexture.Free();
    cbackgroundtexture.Free();
    cbullettexture.Free();
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] )
{





















        for(int i=0;i<BULLETBUFFER;i++)
    {
        cbullet[i].SetTexture(&cbullettexture);
    }
    for(int i=0;i<INICHARNUMBER;i++)
    {
        ccharacter[i].SetTexture(&cchartexture);
    }
    playera.m_playercharacter.SetTexture(&cchartexture);
    playerb.m_playercharacter.SetTexture(&cchartexture);


    playerb.SetBind(0, SDLK_z);
    playerb.SetBind(1, SDLK_s);
    playerb.SetBind(2, SDLK_q);
    playerb.SetBind(3, SDLK_d);
    playerb.SetBind(4, SDLK_u);
    playerb.SetBind(5, SDLK_i);
    playerb.SetBind(6, SDLK_p);

    int nposx[INICHARNUMBER+2];
    int nposy[INICHARNUMBER+2];
    int chardir[INICHARNUMBER*INICHARNUMBER];
    int chardur[INICHARNUMBER*INICHARNUMBER];
    //initialize timer to calculate random movement
    int framesec = 0;      // number of frame in the round
    int spriteframe = 0; // global frame counter to simulate sprites movement (could be individualized)
    //int randcharm = 0;
    int j = 0; //number of round (in order to delete 1 neutral character each round)
    int k = 0; //bullet checker
    int stabframea = 0;
    int stabframeb = 0;
    int shotframea = 0;
    int shotframeb = 0;
    int playerascore = 0;
    int playerbscore = 0;
    bool bulletcheck = false;
    bool gameend = false;
    std::stringstream textbuffer;
    int iswinner = 0;
    bool gamerunning = false;
    bool gamestart = false;
    bool endtimer= false;
    int dticktimer = 0;
    int tickendtimer = 0;


    //Start up SDL and create window
    if( !init() ){printf( "Failed to initialize!\n" );}
    else
    {
        //Load media
        if( !loadMedia() ){printf( "Failed to load media!\n" );}
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }

                    //Handle input
                    playera.HandleEvents(e);
                    playerb.HandleEvents(e);
                }
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                if(!gamerunning)
                {
                    //menu
                    gamerunning=true;
                    gamestart=false;
                }
                else
                {

                    cbackgroundtexture.Render(0,0,0,gRenderer,SDL_FLIP_NONE);





                  if(!gamestart)
                  {
                      framesec = 0;      // number of frame in the round
                      spriteframe = 0; // global frame counter to simulate sprites movement (could be individualized)
                      j = 0; //number of round (in order to delete 1 neutral character each round)
                      k = 0; //bullet checker
                      stabframea = 0;
                      stabframeb = 0;
                      shotframea = 0;
                      shotframeb = 0;
                      bulletcheck = false;
                      gameend = false;
                      iswinner = 0;
                      playera.SetAmmunition(STARTAMMUNITION);
                      playerb.SetAmmunition(STARTAMMUNITION);
                      //initialize timer to calculate random movement

                      srand(time(NULL));

                          for(int i = 0; i<=(INICHARNUMBER+2); i++)
                          {
                              nposx[i] = rand()%(SCREEN_WIDTH-70-20);
                          }

                          for(int i = 0; i<=(INICHARNUMBER+2); i++)
                          {
                              nposy[i] = rand()%(SCREEN_HEIGHT-80-20);
                          }

                          for(int i=0; i<=(INICHARNUMBER*INICHARNUMBER);i++)
                          {
                              chardir[i]= rand()%9;
                              chardur[i]= rand()%(ROUNDTIME-10);
                          }

                          //set character texture and random position

                  for(int i=0;i<INICHARNUMBER;i++)
                  {
                      ccharacter[i].SetPosition(nposx[i],nposy[i]);
                      ccharacter[i].SetVisible(true);
                      ccharacter[i].SetAlive(true);
                  }

                  playera.m_playercharacter.SetAlive(1);
                  playerb.m_playercharacter.SetAlive(1);


                  playera.m_playercharacter.SetPosition(nposx[INICHARNUMBER+1],nposy[INICHARNUMBER+1]);
                  playerb.m_playercharacter.SetPosition(nposx[INICHARNUMBER+2],nposy[INICHARNUMBER+2]);

                   gameend = false;
                  gamestart=true;
                  }




                  if(!gameend)
                  {
               ++framesec;
                spriteframe = (framesec/10)%4;
                if(framesec==ROUNDTIME)
                {
                    framesec=0;
                    if(j<=INICHARNUMBER)
                    {
                        if(ccharacter[j].GetAlive())
                        {
                            ccharacter[j].SetAlive(0);ccharacter[j].SetVisible(0);//ccharacter[j].Free();
                        }
                        j++;
                    }
                }

                textbuffer.str("");
                textbuffer << playerascore ;
                if( !playerascoretext.LoadFromText(textbuffer.str().c_str(),font,gRenderer,{0,0,0}))
                {
                    printf( "Unable to load player_a score text!\n" );
                }
                    textbuffer.str("");
                    textbuffer << playerbscore ;
                    if( !playerbscoretext.LoadFromText(textbuffer.str().c_str(),font,gRenderer,{0,0,0}))
                    {
                        printf( "Unable to load player_b score text!\n" );
                    }
                    textbuffer.str("");
                    textbuffer << playera.GetAmmunition();
                    if( !playerabulletstext.LoadFromText(textbuffer.str().c_str(),font,gRenderer,{0,0,0}))
                    {
                        printf( "Unable to load player_a bullets text!\n" );
                    }
                    textbuffer.str("");
                    textbuffer << playerb.GetAmmunition() ;
                    if( !playerbbulletstext.LoadFromText(textbuffer.str().c_str(),font,gRenderer,{0,0,0}))
                    {
                        printf( "Unable to load player_b bullets text!\n" );
                    }






                SDL_Rect* currentclip = NULL;

                if (j<=INICHARNUMBER)
                {
for(int i=j;i<INICHARNUMBER;i++)
{
                if(ccharacter[i].GetAlive())
                {

                    if( framesec == 0)
                {
                   // randcharm = rand()%9;

                    switch(chardir[i+j*INICHARNUMBER])
                    {
                        case 0: ccharacter[i].SetVelocity(0,0); break;
                        case 1: ccharacter[i].SetVelocity(CHARSPEED,0); if(!ccharacter[i].GetOrientation()){ccharacter[i].SetOrientation(1);} break;
                        case 2: ccharacter[i].SetVelocity(-CHARSPEED,0);if(ccharacter[i].GetOrientation()){ccharacter[i].SetOrientation(0);} break;
                        case 3: ccharacter[i].SetVelocity(0,CHARSPEED); break;
                        case 4: ccharacter[i].SetVelocity(0,-CHARSPEED); break;
                        case 5: ccharacter[i].SetVelocity(CHARSPEED,CHARSPEED);if(!ccharacter[i].GetOrientation()){ccharacter[i].SetOrientation(1);} break;
                        case 6: ccharacter[i].SetVelocity(-CHARSPEED,-CHARSPEED);if(ccharacter[i].GetOrientation()){ccharacter[i].SetOrientation(0);} break;
                        case 7: ccharacter[i].SetVelocity(CHARSPEED,-CHARSPEED);if(!ccharacter[i].GetOrientation()){ccharacter[i].SetOrientation(1);} break;
                        case 8: ccharacter[i].SetVelocity(-CHARSPEED,CHARSPEED);if(ccharacter[i].GetOrientation()){ccharacter[i].SetOrientation(0);} break;
                    }
                }
                }
}
                }

for(int i=0;i<INICHARNUMBER;i++)
{
    if(ccharacter[i].GetVisible())
    {
    if(ccharacter[i].GetAlive())
        {
                if((framesec<chardur[i+j*INICHARNUMBER]) && (ccharacter[i].GetVelocity()!=0))
                {
               // spriteframe = (framesec/10)%4;
                currentclip = &spriteclips[spriteframe];
                ccharacter[i].IsMoving(SCREEN_WIDTH,SCREEN_HEIGHT);

                }
                else
                {
                ccharacter[i].SetVelocity(0,0);
                currentclip = &spriteclips[0];
                }
         }
    else
    {
        currentclip = &spriteclips[12];
    }
          ccharacter[i].Render(currentclip, gRenderer); //the flip should be in characterclass instead.
    }
}

 if(playera.m_playercharacter.GetAlive())
 {
if (playera.GetFiring() || (shotframea)>0)
{
    shotframea++;
    if(shotframea==20){shotframea=0;}
    currentclip = &spriteclips[8+(shotframea/5)];
    if(shotframea==10 && (playera.GetAmmunition()>0))
    {

        bulletcheck = false;
        k = 0;
        while(!bulletcheck)
       {
            if(!cbullet[k].GetIsAlive())
            {
                bulletcheck = true;
                cbullet[k].SetIsAlive(playera.m_playercharacter.GetOrientation(),playera.m_playercharacter.GetPosX(),playera.m_playercharacter.GetPosY());
                playera.DepleteAmmunition();
            }
            k++;
                    if(k==BULLETBUFFER){printf("bulleft frame reached ! \n"); bulletcheck = true;}
        }
    }







}
else
{
    if (playera.GetStabbing() || (stabframea>0))
    {
        stabframea++;
        if (stabframea==20){stabframea=0;
            for(int i=0;i<INICHARNUMBER;i++)
            {

              if(checkcollision(playera.m_playercharacter.GetRect(),ccharacter[i].GetRect())){ccharacter[i].SetAlive(0);}
            }
            if(checkcollision(playera.m_playercharacter.GetRect(),playerb.m_playercharacter.GetRect())){playerb.m_playercharacter.SetAlive(0);}

        }
        currentclip = &spriteclips[4+(stabframea/5)];
    }
else
{
    playera.IsMoving(SCREEN_WIDTH,SCREEN_HEIGHT);
    if(playera.m_playercharacter.GetVelocity()>0)
    {
        currentclip = &spriteclips[spriteframe];
    }
    else
    {
        currentclip = &spriteclips[0];
    }
}
}
 }
 else
 {
      currentclip = &spriteclips[12];
 }
playera.m_playercharacter.Render(currentclip,gRenderer);




if (playerb.m_playercharacter.GetAlive())
{

if ((playerb.GetFiring() || (shotframeb)>0) && (stabframeb==0))
{
    shotframeb++;
    if(shotframeb==20){shotframeb=0;}
    currentclip = &spriteclips[8+(shotframeb/5)];
    if(shotframeb==10 && (playerb.GetAmmunition()>0))
    {

        bulletcheck = false;
        k = 0;
        while(!bulletcheck)
       {
            if(!cbullet[k].GetIsAlive())
            {
                bulletcheck = true;
                cbullet[k].SetIsAlive(playerb.m_playercharacter.GetOrientation(),playerb.m_playercharacter.GetPosX(),playerb.m_playercharacter.GetPosY());
                playerb.DepleteAmmunition();

            }
            k++;
                    if(k==BULLETBUFFER){printf("bulleft frame reached ! \n"); bulletcheck = true;}
        }
    }
}
else
{
if (playerb.GetStabbing() || (stabframeb>0))
{
    stabframeb++;
    if (stabframeb==20){stabframeb=0;
        for(int i=0;i<INICHARNUMBER;i++)
        {

          if(checkcollision(playerb.m_playercharacter.GetRect(),ccharacter[i].GetRect())){ccharacter[i].SetAlive(0);}
        }
        if(checkcollision(playerb.m_playercharacter.GetRect(),playera.m_playercharacter.GetRect())){playera.m_playercharacter.SetAlive(0);}

    }
    currentclip = &spriteclips[4+(stabframeb/5)];
}
else
{
    playerb.IsMoving(SCREEN_WIDTH,SCREEN_HEIGHT);
    if(playerb.m_playercharacter.GetVelocity()>0)
    {
        currentclip = &spriteclips[spriteframe];
    }
    else
    {
        currentclip = &spriteclips[0];
    }
}
}
}
else
{
    currentclip = &spriteclips[12];
}





playerb.m_playercharacter.Render(currentclip,gRenderer);

for(int i=0;i<BULLETBUFFER;i++)
{
if(cbullet[i].GetIsAlive())
    {
 cbullet[i].IsMoving(SCREEN_WIDTH);
 for(int m=0;m<INICHARNUMBER;m++)
 {
     if(ccharacter[m].GetAlive() && ccharacter[m].GetVisible()){
   if(checkcollision(cbullet[i].GetRect(),ccharacter[m].GetRect())){ccharacter[m].SetAlive(0);cbullet[i].SetIsDead();}
     }
 }
 if(checkcollision(cbullet[i].GetRect(),playerb.m_playercharacter.GetRect())){playerb.m_playercharacter.SetAlive(0);cbullet[i].SetIsDead();}
 if(checkcollision(cbullet[i].GetRect(),playera.m_playercharacter.GetRect())){playera.m_playercharacter.SetAlive(0);cbullet[i].SetIsDead();}

 cbullet[i].Render(gRenderer);
    }
}

if(!gameend)
{
if(!playera.m_playercharacter.GetAlive())
{
    if(!playerb.m_playercharacter.GetAlive()){gameend = true;}
    else{playerascore+=1; iswinner = 1; gameend = true;}
}
if(!playerb.m_playercharacter.GetAlive())
{
    if(!playera.m_playercharacter.GetAlive()){gameend = true;}
    else{playerbscore+=1;iswinner = 2; gameend = true;}
}
}


playerascoretext.Render(2*PTSIZE,2,0,gRenderer,SDL_FLIP_NONE);
playerabulletstext.Render(1./10*SCREEN_WIDTH+2*PTSIZE,2,0,gRenderer,SDL_FLIP_NONE);
playerbbulletstext.Render(9./10*SCREEN_WIDTH-2*PTSIZE,2,0,gRenderer,SDL_FLIP_NONE);
playerbscoretext.Render(SCREEN_WIDTH-2*PTSIZE,2,0,gRenderer,SDL_FLIP_NONE);
                  }
                  else
                  {
                      if((dticktimer > 0) || (!endtimer))
                      {

                          if(!endtimer)
                          {
                              tickendtimer = SDL_GetTicks();
                              endtimer = true;
                              dticktimer = 3000;

                          }
                          else
                          {
                              dticktimer = 3000 - (SDL_GetTicks() - tickendtimer);
                              textbuffer.str("");
                              textbuffer << "Player " << iswinner  << " Win ! New Game Starting in : "<< dticktimer/1000;
                              if( !winnertext.LoadFromText(textbuffer.str().c_str(),font,gRenderer,{0xFF,0,0}))
                              {
                                  printf( "Unable to load player_a score text!\n" );
                              }
                              winnertext.Render((1./2)*(SCREEN_WIDTH-winnertext.GetWidth()),1./10*SCREEN_HEIGHT,0,gRenderer,SDL_FLIP_NONE);
                          }
                       }
                       else
                       {
                       gamerunning = false;
                       gameend = false;
                       endtimer = false;
                       tickendtimer = 0;
                       dticktimer = 0;
                       }




                      //gamerunning = false;
                      //gameend = false;
                  }
                //Update screen


}
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}





