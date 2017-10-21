//Using SDL, SDL_image, standard IO, and strings
#include <ccharacter.h>
#include <ctexture.h>
#include <cbullet.h>
#include <stdlib.h>
#include <cplayer.h>
#include <sstream>
#include <time.h>
#include <fstream>


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
//const int PTSIZE = 28;
//The application time based timer


//Starts up SDL and creates window
bool init();
bool checkcollision(SDL_Rect a, SDL_Rect b);
//Loads media
bool loadMedia();
void gamerun();
bool checkmousecollision(SDL_Point a, SDL_Rect b);
void keyforbiddeninit();
void readfile();
void savefile(int newkeyvalue);
int loadfile(int linej);

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

CTexture cbackgroundtexture;
CTexture cmenupathtext;
CTexture cmenubuttonquittext;
CTexture cmenubuttonoptionstext;
CTexture cmenubuttonstarttext;
CTexture quitmenubuttonconfirm;
CTexture quitmenubuttonback;
CTexture quitqueestiontext;
CTexture keybindinputtext[14];
CTexture keybindbacktext;

CTexture keybindbuttonconfirm;
CTexture keybindbuttonback;
CTexture keybindcommandtext;

CTexture pausequeestiontext;
CTexture pausequeestiontextb;
CTexture pausemenubuttonconfirm;
CTexture pausemenubuttonback;

CTexture optionmenubuttonconfirm;
CTexture optionmenubuttonback;
CTexture optionqueestiontext;

SDL_Rect cmenubuttonquitrect;
SDL_Rect cmenubuttonoptionsrect;
SDL_Rect cmenubuttonstartrect;
SDL_Rect quitmenurectconfirm;
SDL_Rect quitmenurectback;
SDL_Rect pausemenurectconfirm;
SDL_Rect pausemenurectback;
SDL_Rect optionmenurectconfirm;
SDL_Rect optionmenurectback;


SDL_Rect keybindinputrect[14];
SDL_Rect keybindbackrect;
CTexture keybindrectconfirm;
CTexture keybindrectback;

SDL_Point cmousepointer;
SDL_Color basecolor = {0xFF,0xFF,0xFF};
SDL_Color highlightcolor = {0x00,0x00,0xFF};
bool keylock = false;
bool quitflag = false;
bool gameflag = false;
bool optionflag = false;
bool upflag = false;
bool downflag = false;
bool leftflag = false;
bool rightflag = false;
bool esclock = false;
bool optionconfirmscreen = false;
bool gameplay = false;
bool gamepause = false;
bool optionmenu = false;
bool optionconfirm = false;
bool optionback = false;
bool quitmenu = false;
bool gamemenu = true;
bool quitgameflag = false;

bool keybindchange = false;
bool keybindcommandcall = false;
bool keybindcommandnew = false;
        bool keybindcommand =false;

bool quitconfirm = false;
bool quitback = false;
bool pauseconfirm = false;
bool pauseback = false;

int cpausebuttonplace = 1;
int cquitbuttonplace = 1;
int    cmenubuttonflag = 1;
int keybindselect = 0;
int keybindactivate = 15;
int menuticktimer = 0;
int currentick = 0;
int coptionbuttonplace = 1;
TTF_Font *font24 = NULL;
TTF_Font *font42 = NULL;

CTexture keybindoutputtext[14];
std::stringstream textkeybindbuffer;
int keyvalue[14];
int keyforbidden[72];
bool keyisforbidden = false;


void keyforbiddeninit()
{
keyforbidden[0] = SDLK_AC_BACK;
keyforbidden[1] = SDLK_AC_BOOKMARKS;
keyforbidden[2] = SDLK_AC_FORWARD;
keyforbidden[3] = SDLK_AC_HOME;
keyforbidden[4] = SDLK_AC_REFRESH;
keyforbidden[5] = SDLK_AC_SEARCH;
keyforbidden[6] = SDLK_AC_STOP;
keyforbidden[7] = SDLK_AGAIN;
keyforbidden[8] = SDLK_ALTERASE;
keyforbidden[9] = SDLK_QUOTE;
keyforbidden[10] = SDLK_APPLICATION;
keyforbidden[11] = SDLK_AUDIOMUTE;
keyforbidden[12] = SDLK_AUDIONEXT;
keyforbidden[13] = SDLK_AUDIOPLAY;
keyforbidden[14] = SDLK_AUDIOSTOP;
keyforbidden[15] = SDLK_AUDIOPREV;
keyforbidden[16] = SDLK_BRIGHTNESSDOWN;
keyforbidden[17] = SDLK_BRIGHTNESSUP;
keyforbidden[18] = SDLK_CALCULATOR;
keyforbidden[19] = SDLK_CANCEL;
keyforbidden[20] = SDLK_CAPSLOCK;
keyforbidden[21] = SDLK_CLEAR;
keyforbidden[22] = SDLK_CLEARAGAIN;
keyforbidden[23] = SDLK_COMPUTER;
keyforbidden[24] = SDLK_COPY;
keyforbidden[25] = SDLK_CRSEL;
keyforbidden[26] = SDLK_CURRENCYSUBUNIT;
keyforbidden[27] = SDLK_CURRENCYUNIT;
keyforbidden[28] = SDLK_CUT;
keyforbidden[29] = SDLK_DECIMALSEPARATOR;
keyforbidden[30] = SDLK_DELETE;
keyforbidden[31] = SDLK_DISPLAYSWITCH;
keyforbidden[32] = SDLK_EJECT;
keyforbidden[33] = SDLK_END;
keyforbidden[34] = SDLK_ESCAPE;
keyforbidden[35] = SDLK_EXECUTE;
keyforbidden[36] = SDLK_EXSEL;
keyforbidden[37] = SDLK_FIND;
keyforbidden[38] = SDLK_HELP;
keyforbidden[39] = SDLK_HOME;
keyforbidden[40] = SDLK_INSERT;
keyforbidden[41] = SDLK_KBDILLUMDOWN;
keyforbidden[42] = SDLK_KBDILLUMTOGGLE;
keyforbidden[43] = SDLK_KBDILLUMUP;
keyforbidden[44] = SDLK_LALT;
keyforbidden[45] = SDLK_LCTRL;
keyforbidden[46] = SDLK_LGUI;
keyforbidden[47] = SDLK_LSHIFT;
keyforbidden[48] = SDLK_MAIL;
keyforbidden[49] = SDLK_MEDIASELECT;
keyforbidden[50] = SDLK_MENU;
keyforbidden[51] = SDLK_MODE;
keyforbidden[52] = SDLK_MUTE;
keyforbidden[53] = SDLK_NUMLOCKCLEAR;
keyforbidden[54] = SDLK_OPER;
keyforbidden[55] = SDLK_OUT;
keyforbidden[56] = SDLK_PAGEDOWN;
keyforbidden[57] = SDLK_PAGEUP;
keyforbidden[58] = SDLK_POWER;
keyforbidden[59] = SDLK_PASTE;
keyforbidden[60] = SDLK_PRINTSCREEN;
keyforbidden[61] = SDLK_PRIOR;
keyforbidden[62] = SDLK_RALT;
keyforbidden[63] = SDLK_RCTRL;
keyforbidden[64] = SDLK_RGUI;
keyforbidden[65] = SDLK_RSHIFT;
keyforbidden[66] = SDLK_SCROLLLOCK;
keyforbidden[67] = SDLK_SEPARATOR;
keyforbidden[68] = SDLK_STOP;
keyforbidden[69] = SDLK_SYSREQ;
keyforbidden[70] = SDLK_VOLUMEUP;
keyforbidden[71] = SDLK_VOLUMEDOWN;
}


void readfile()
{
    std::stringstream text;
    std::ifstream myfile;
    myfile.open("keybinds.cfg");
    std::string line;
    if(myfile.is_open())
    {
        text.str("");
        while(std::getline(myfile,line))
        {
            std::istringstream is_line(line);
            std::string key;
            if(std::getline(is_line,key,'='))
            {
                std::string value;
                if(std::getline(is_line,value))
                {
                    text << value << "\n";
                }
            }
        }

       // text << line << "\n";
       // lines.push_back(line);

        myfile.close();
        printf("%s",text.str().c_str());
    }
    else
    {
        printf("Unable to open file \n");
    }
}

int loadfile(int linej)
{
    int loadedvalue;
    std::stringstream text;
    std::ifstream myfile;
    myfile.open("keybinds.cfg");
    std::string line;
    int j=0;
    if(myfile.is_open())
    {
        text.str("");
        while(std::getline(myfile,line) && j<14)
        {
            std::istringstream is_line(line);
            std::string key;
            if(std::getline(is_line,key,'='))
            {
                std::string value;
                if(std::getline(is_line,value))
                {
                    std::istringstream ss(value);
                    if(j==linej)
                    {
                    ss >> loadedvalue;
                    }
                }
            }
            j+=1;
        }

       // text << line << "\n";
       // lines.push_back(line);

        myfile.close();
    }
    else
    {
        printf("Unable to open file \n");
    }
    return loadedvalue;
}

void savefile(int newkeyvalue[14])
{
    std::ofstream myfile;
    std::stringstream text;
    myfile.open("keybinds.cfg");
    if(myfile.is_open())
    {
        for(int i=0;i<14;i++)
        {
        text.str("");
        text<<"keyvalue"<<i<<"="<<newkeyvalue[i]<<"\n";
        myfile<<text.str().c_str();
        }
        myfile.close();
    }
    else
    {
        printf("Unable to open file \n");
    }
}





























//Scene textures
CTexture cchartexture;
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

    font24 = TTF_OpenFont("Font/joystix monospace.ttf",24);
    if(font24 == NULL){printf("Failed to load font! SDL_TTF error : %s\n",TTF_GetError());success = false;}
    font42 = TTF_OpenFont("Font/joystix monospace.ttf",42);
    if(font42 == NULL){printf("Failed to load font! SDL_TTF error : %s\n",TTF_GetError());success = false;}





    return success;
}

void close()
{
    //Free loaded images (game)
    cchartexture.Free();
    cbackgroundtexture.Free();
    cbullettexture.Free();
    //Free loaded images (menu)

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();    
}

bool checkmousecollision(SDL_Point a, SDL_Rect b)
{
    if((a.x)<b.x){return false;}
    if(a.x>(b.x+b.w)){return false;}
    if((a.y)<(b.y)){return false;}
    if(a.y>(b.y+b.h)){return false;}
    return true;
}




int main( int argc, char* args[] )
{

    keyforbiddeninit();
    keyvalue[0] = loadfile(0);
    keyvalue[1] = loadfile(1);
    keyvalue[2] = loadfile(2);
    keyvalue[3] = loadfile(3);
    keyvalue[4] = loadfile(4);
    keyvalue[5] = loadfile(5);
    keyvalue[6] = loadfile(6);
    keyvalue[7] = loadfile(7);
    keyvalue[8] = loadfile(8);
    keyvalue[9] = loadfile(9);
    keyvalue[10] = loadfile(10);
    keyvalue[11] = loadfile(11);
    keyvalue[12] = loadfile(12);
    keyvalue[13] = loadfile(13);

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
    menuticktimer = 0;
    bool quitflag = false;
    bool optionflag = false;
    bool gameflag = false;












    playera.SetBind(0, keyvalue[0]);
    playera.SetBind(1, keyvalue[1]);
    playera.SetBind(2, keyvalue[2]);
    playera.SetBind(3, keyvalue[3]);
    playera.SetBind(4, keyvalue[4]);
    playera.SetBind(5, keyvalue[5]);
    playera.SetBind(6, keyvalue[6]);
    playerb.SetBind(0, keyvalue[7]);
    playerb.SetBind(1, keyvalue[8]);
    playerb.SetBind(2, keyvalue[9]);
    playerb.SetBind(3, keyvalue[10]);
    playerb.SetBind(4, keyvalue[11]);
    playerb.SetBind(5, keyvalue[12]);
    playerb.SetBind(6, keyvalue[13]);




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
                quitflag = false;
                optionflag = false;
                gameflag = false;
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    else
                    {
                    if(gamemenu)
                    {
                        keybindchange=false;
                        quitmenu = false;
                        quitback = false;
                        gameplay = false;
                        optionmenu = false;
                        keybindactivate = 15;
                        optionconfirm = false;

                    if(e.type == SDL_KEYDOWN)
                    {
                        switch(e.key.keysym.sym)
                        {
                        case SDLK_UP:
                            upflag = true;
                            keylock = false;
                            break;
                        case SDLK_DOWN:
                            keylock = false;
                            downflag = true;
                            break;
                        case SDLK_RETURN:
                            keylock = true;
                            break;
                        case SDLK_ESCAPE:
                            if (keylock == false && esclock == false)
                            {
                                if(quitmenu)
                                {
                                    quitmenu= false;
                                    gamemenu = true;

                                }
                                else if(gamemenu)
                                {
                                    quitmenu= true;
                                    gamemenu = false;
                                }
                                esclock = true;
                            }
                            break;

                        default :
                            keylock = false;
                            break;
                        }
                    }
                    else if((e.type == SDL_MOUSEBUTTONDOWN))
                    {
                        if (e.button.button == SDL_BUTTON_LEFT)
                        {

                                if(checkmousecollision(cmousepointer, cmenubuttonstartrect))
                                {
                                     keylock = true;
                                }
                                else if(checkmousecollision(cmousepointer, cmenubuttonoptionsrect))
                                {
                                    keylock = true;
                                }
                                else if(checkmousecollision(cmousepointer, cmenubuttonquitrect))
                                {
                                    keylock = true;
                                }

                        }
                    }
                    else if((e.type == SDL_MOUSEMOTION))
                    {
                        SDL_GetMouseState(&cmousepointer.x,&cmousepointer.y);

                        if(checkmousecollision(cmousepointer, cmenubuttonstartrect))
                        {
                            cmenubuttonflag = 1;
                        }
                        else if(checkmousecollision(cmousepointer, cmenubuttonoptionsrect))
                        {
                            cmenubuttonflag = 2;
                        }
                        else if(checkmousecollision(cmousepointer, cmenubuttonquitrect))
                        {
                            cmenubuttonflag = 3;
                        }
                        else
                        {
                           // cmenubuttonflag = 0;
                        }

                    }
                    else if((e.type == SDL_MOUSEBUTTONUP))
                    {
                        if(keylock == true){
                            if(checkmousecollision(cmousepointer, cmenubuttonstartrect))
                            {
                                gameflag = true;
                            }
                            else if(checkmousecollision(cmousepointer, cmenubuttonoptionsrect))
                            {
                                optionflag = true;
                            }
                            else if(checkmousecollision(cmousepointer, cmenubuttonquitrect))
                            {
                                quitflag = true;
                            }
                            }
                        keylock = false;
                    }
                    else if(e.type == SDL_KEYUP)
                    {
                        if(keylock == true){
                            if (cmenubuttonflag == 1){ gameflag = true;}
                            else if (cmenubuttonflag ==2){optionflag = true;}
                            else if (cmenubuttonflag == 3){quitflag = true;}



                             }
                            keylock = false;
                            upflag = false;
                            downflag = false;
                             esclock = false;

                    }
                    }
                    else if(quitmenu)
                    {
                        quitflag = false;

                        if(e.type == SDL_KEYDOWN)
                        {
                            switch(e.key.keysym.sym)
                            {
                            case SDLK_UP:
                                upflag = true;
                                keylock = false;
                                break;
                            case SDLK_DOWN:
                                keylock = false;
                                downflag = true;
                                break;
                            case SDLK_LEFT:
                                keylock = false;
                                leftflag = true;
                                break;
                            case SDLK_RIGHT:
                                keylock = false;
                                rightflag = true;
                                break;
                            case SDLK_RETURN:
                                keylock = true;
                                break;
                            case SDLK_ESCAPE:
                                if (keylock == false && esclock == false)
                                {
                                    if(quitmenu)
                                    {
                                        quitmenu= false;
                                        gamemenu = true;

                                    }
                                    else if(gamemenu)
                                    {
                                        quitmenu= true;
                                        gamemenu = false;
                                    }
                                    esclock = true;
                                }
                                keylock = false;
                            default :
                                keylock = false;
                                break;
                            }
                        }
                        else if((e.type == SDL_MOUSEBUTTONDOWN))
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {

                                    if(checkmousecollision(cmousepointer,quitmenurectconfirm))
                                    {
                                         keylock = true;
                                    }
                                    else if(checkmousecollision(cmousepointer, quitmenurectback))
                                    {
                                        keylock = true;
                                    }
                            }
                        }
                        else if((e.type == SDL_MOUSEMOTION))
                        {
                            SDL_GetMouseState(&cmousepointer.x,&cmousepointer.y);

                            if(checkmousecollision(cmousepointer, quitmenurectconfirm))
                            {
                                cquitbuttonplace = 1;
                            }
                            else if(checkmousecollision(cmousepointer, quitmenurectback))
                            {
                                cquitbuttonplace = 2;
                            }

                        }
                        else if((e.type == SDL_MOUSEBUTTONUP))
                        {
                            if(keylock == true){
                                if(checkmousecollision(cmousepointer,  quitmenurectconfirm))
                                {
                                    quitconfirm = true;
                                }
                                else if(checkmousecollision(cmousepointer, quitmenurectback))
                                {
                                   quitback = true;
                                }
                                }
                            keylock = false;
                        }
                        else if(e.type == SDL_KEYUP)
                        {
                            if(keylock == true){
                                if (cquitbuttonplace == 1){ quitconfirm = true;}
                                else if (cquitbuttonplace ==2){quitback = true;}
                                 }
                                keylock = false;
                                upflag = false;
                                downflag = false;
                                leftflag = false;
                                rightflag = false;
                                esclock = false;
                        }
                    }
                    else if(optionmenu)
                    {

                        optionconfirmscreen = false;
                        quitmenu = false;
                        quitback = false;
                        gameplay = false;
                        gamemenu = false;
                        optionback = false;
                        optionconfirm = false;
                    if(e.type == SDL_KEYDOWN)
                    {
                        switch(e.key.keysym.sym)
                        {
                        case SDLK_UP:
                            upflag = true;
                            keylock = false;
                            break;
                        case SDLK_DOWN:
                            keylock = false;
                            downflag = true;
                            break;
                        case SDLK_RETURN:
                            keylock = true;
                            break;
                        case SDLK_ESCAPE:
                            if (keylock == false && esclock == false)
                            {
                                if(optionmenu == true )
                                {
                                    if(keybindchange==false)
                                    {
                                    gamemenu= true;
                                    optionmenu = false;
                                    }
                                    else
                                    {
                                    optionmenu = false;
                                    optionconfirmscreen = true;
                                    }

                                }
                                esclock = true;
                            }
                            break;

                        default :
                            keylock = false;

                            break;
                        }
                    }
                    else if((e.type == SDL_MOUSEBUTTONDOWN))
                    {
                        if (e.button.button == SDL_BUTTON_LEFT)
                        {
                                for(int i = 0; i<14; i++)
                                {
                                if(checkmousecollision(cmousepointer, keybindinputrect[i]))
                                {
                                     keylock = true;
                                }
                                }
                                if(checkmousecollision(cmousepointer, keybindbackrect))
                                {
                                     keylock = true;
                                }
                        }
                    }
                    else if((e.type == SDL_MOUSEMOTION))
                    {
                        SDL_GetMouseState(&cmousepointer.x,&cmousepointer.y);

                        for(int i = 0; i<14; i++)
                        {
                        if(checkmousecollision(cmousepointer, keybindinputrect[i]))
                        {
                             keybindselect = i;
                        }
                        }
                        if(checkmousecollision(cmousepointer, keybindbackrect))
                        {
                             keybindselect = 14;
                        }

                    }
                    else if((e.type == SDL_MOUSEBUTTONUP))
                    {
                        if(keylock == true){
                            for(int i = 0; i<14; i++)
                            {
                            if(checkmousecollision(cmousepointer, keybindinputrect[i]))
                            {
                                 keybindactivate = i;
                            }
                            }
                            if(checkmousecollision(cmousepointer, keybindbackrect))
                            {
                                 keybindactivate = 14;
                            }
                            }
                        keylock = false;
                    }
                    else if(e.type == SDL_KEYUP)
                    {
                        if(keylock == true){
                            for(int i = 0; i<15; i++)
                            {
                            if (keybindselect == i){ keybindactivate = i;}
                           }
                             }
                            keylock = false;
                            upflag = false;
                            downflag = false;
                            esclock = false;
                    }
                    }
                    else if (optionconfirmscreen)
                    {
                        keybindactivate = 15;
                        optionmenu = false;
                       if(e.type == SDL_KEYDOWN)
                        {
                            switch(e.key.keysym.sym)
                            {
                            case SDLK_UP:
                                upflag = true;
                                keylock = false;
                                break;
                            case SDLK_DOWN:
                                keylock = false;
                                downflag = true;
                                break;
                            case SDLK_LEFT:
                                keylock = false;
                                leftflag = true;
                                break;
                            case SDLK_RIGHT:
                                keylock = false;
                                rightflag = true;
                                break;
                            case SDLK_RETURN:
                                keylock = true;
                                break;
                            case SDLK_ESCAPE:
                                if (keylock == false && esclock==false)
                                {
                                    if(optionconfirmscreen)
                                    {
                                        optionconfirmscreen = false;
                                        optionmenu = true;

                                    }
                                    esclock = true;
                                }
                                keylock = false;
                            default :
                                keylock = false;
                                break;
                            }
                        }
                        else if((e.type == SDL_MOUSEBUTTONDOWN))
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {

                                    if(checkmousecollision(cmousepointer,optionmenurectconfirm))
                                    {
                                         keylock = true;
                                    }
                                    else if(checkmousecollision(cmousepointer, optionmenurectback))
                                    {
                                        keylock = true;
                                    }
                            }
                        }
                        else if((e.type == SDL_MOUSEMOTION))
                        {
                            SDL_GetMouseState(&cmousepointer.x,&cmousepointer.y);

                            if(checkmousecollision(cmousepointer, optionmenurectconfirm))
                            {
                                coptionbuttonplace = 1;
                            }
                            else if(checkmousecollision(cmousepointer, optionmenurectback))
                            {
                                coptionbuttonplace = 2;
                            }

                        }
                        else if((e.type == SDL_MOUSEBUTTONUP))
                        {
                            if(keylock == true){
                                if(checkmousecollision(cmousepointer,  optionmenurectconfirm))
                                {
                                    optionconfirm = true;
                                }
                                else if(checkmousecollision(cmousepointer, optionmenurectback))
                                {
                                   optionback = true;
                                }
                                }
                            keylock = false;
                        }
                        else if(e.type == SDL_KEYUP)
                        {
                            if(keylock == true){
                                if (coptionbuttonplace == 1){ optionconfirm = true;}
                                else if (coptionbuttonplace ==2){optionback = true;}
                                 }
                                keylock = false;
                                upflag = false;
                                downflag = false;
                                leftflag = false;
                                rightflag = false;
                                esclock = false;
                        }







                    }
                    else if (keybindcommand)
                    {

                        keybindactivate = 15;
                        keyisforbidden = false;
                        if(e.type == SDL_KEYDOWN)
                        {
                            if(e.key.keysym.sym == SDLK_ESCAPE)
                            {
                                if (keylock == false && esclock==false)
                                {
                                    if(keybindcommand)
                                    {
                                        optionmenu = true;
                                        keybindcommand = false;

                                    }
                                    esclock = true;
                                }


                            }
                            else
                            {
                                for(int i=0;i<72;i++)
                              {
                                    if(e.key.keysym.sym==keyforbidden[i]){keyisforbidden = true;}
                              }
                            if(!keyisforbidden)
                            {
                            keyvalue[keybindselect] = e.key.keysym.sym;
                            for(int i=0;i<14;i++)
                            {
                                if(i !=keybindselect){
                                if(keyvalue[keybindselect] == keyvalue[i]){keyvalue[i] = NULL;}
                                }
                            }
                            keybindchange = true;
                            }
                            if(keybindcommand)
                            {
                            optionmenu = true;
                            keybindcommand = false;
                            }
                            keylock = false;
                             }







                        }
                        else if(e.type == SDL_KEYUP)
                        {
                                keylock = false;
                                upflag = false;
                                downflag = false;
                                leftflag = false;
                                rightflag = false;
                                esclock = false;
                        }




                    }
                    else if (gameplay)
                    {
                        //Handle input
                        playera.HandleEvents(e);
                        playerb.HandleEvents(e);
                        gamepause = false;
                        pauseconfirm = false;
                        pauseback = false;
                       if(e.type == SDL_KEYDOWN)
                        {
                            switch(e.key.keysym.sym)
                            {
                            case SDLK_ESCAPE:
                                if (keylock == false && esclock == false)
                                {
                                    if(gamepause)
                                    {
                                        gamepause = false;
                                        gameplay = true;

                                    }
                                    else if(gameplay)
                                    {
                                        gamepause= true;
                                        gameplay = false;
                                    }
                                    esclock = true;
                                }
                            default :
                                keylock = false;
                                break;
                            }
                        }
                        else if(e.type == SDL_KEYUP)
                        {
                                keylock = false;
                                esclock = false;
                        }
                    }
                    else if (gamepause)
                    {
                        quitgameflag = false;

                        if(e.type == SDL_KEYDOWN)
                        {
                            switch(e.key.keysym.sym)
                            {
                            case SDLK_UP:
                                upflag = true;
                                keylock = false;
                                break;
                            case SDLK_DOWN:
                                keylock = false;
                                downflag = true;
                                break;
                            case SDLK_LEFT:
                                keylock = false;
                                leftflag = true;
                                break;
                            case SDLK_RIGHT:
                                keylock = false;
                                rightflag = true;
                                break;
                            case SDLK_RETURN:
                                keylock = true;
                                break;
                            case SDLK_ESCAPE:
                                if (keylock == false && esclock==false)
                                {
                                    if(gamepause)
                                    {
                                        gamepause = false;
                                        gameplay = true;

                                    }
                                    else if(gameplay)
                                    {
                                        gamepause= true;
                                        gameplay = false;
                                    }
                                    esclock = true;
                                }
                                keylock = false;
                            default :
                                keylock = false;
                                break;
                            }
                        }
                        else if((e.type == SDL_MOUSEBUTTONDOWN))
                        {
                            if (e.button.button == SDL_BUTTON_LEFT)
                            {

                                    if(checkmousecollision(cmousepointer,pausemenurectconfirm))
                                    {
                                         keylock = true;
                                    }
                                    else if(checkmousecollision(cmousepointer, pausemenurectback))
                                    {
                                        keylock = true;
                                    }
                            }
                        }
                        else if((e.type == SDL_MOUSEMOTION))
                        {
                            SDL_GetMouseState(&cmousepointer.x,&cmousepointer.y);

                            if(checkmousecollision(cmousepointer, pausemenurectconfirm))
                            {
                                cpausebuttonplace = 1;
                            }
                            else if(checkmousecollision(cmousepointer, pausemenurectback))
                            {
                                cpausebuttonplace = 2;
                            }

                        }
                        else if((e.type == SDL_MOUSEBUTTONUP))
                        {
                            if(keylock == true){
                                if(checkmousecollision(cmousepointer,  pausemenurectconfirm))
                                {
                                    pauseconfirm = true;
                                }
                                else if(checkmousecollision(cmousepointer, pausemenurectback))
                                {
                                   pauseback = true;
                                }
                                }
                            keylock = false;
                        }
                        else if(e.type == SDL_KEYUP)
                        {
                            if(keylock == true){
                                if (cpausebuttonplace == 1){ pauseconfirm = true;}
                                else if (cpausebuttonplace ==2){pauseback = true;}
                                 }
                                keylock = false;
                                upflag = false;
                                downflag = false;
                                leftflag = false;
                                rightflag = false;
                                esclock = false;
                        }







                    }
                    else{printf("error, unavailable screen \n");gamemenu = true;}


                    }



                }
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                if(!gameplay)
                {
                    currentick = SDL_GetTicks();

                        if(quitmenu)
                    {
                    if(leftflag==true || rightflag==true)
                    {

                        if(currentick-menuticktimer > 200)
                        {
                        if(leftflag==true && rightflag == false)
                        {
                            if(cquitbuttonplace == 2){cquitbuttonplace -= 1;}
                            else{cquitbuttonplace += 1;}
                            menuticktimer = SDL_GetTicks();

                        }
                        else if(leftflag == false && rightflag == true)
                        {
                            if(cquitbuttonplace == 2){cquitbuttonplace -= 1;}
                            else{cquitbuttonplace += 1;}
                            menuticktimer = SDL_GetTicks();

                        }
                        }

                    }
                    }
                        else if(gamemenu)
                    {
                        if(upflag==true || downflag==true)
                        {

                            if(currentick-menuticktimer > 200)
                            {
                            if(upflag==true &&downflag == false)
                            {
                                if(cmenubuttonflag>1){cmenubuttonflag -= 1;}
                                else{cmenubuttonflag = 3;}
                                menuticktimer = SDL_GetTicks();
                            }
                            else if(upflag == false && downflag == true)
                            {
                                if(cmenubuttonflag<3){cmenubuttonflag += 1;}
                                else{cmenubuttonflag = 1;}
                                menuticktimer = SDL_GetTicks();
                            }
                            }

                        }
                    }
                        else if(gamepause)
                        {
                        if(leftflag==true || rightflag==true)
                        {

                            if(currentick-menuticktimer > 200)
                            {
                            if(leftflag==true && rightflag == false)
                            {
                                if(cpausebuttonplace == 2){cpausebuttonplace -= 1;}
                                else{cpausebuttonplace += 1;}
                                menuticktimer = SDL_GetTicks();

                            }
                            else if(leftflag == false && rightflag == true)
                            {
                                if(cpausebuttonplace == 2){cpausebuttonplace -= 1;}
                                else{cpausebuttonplace += 1;}
                                menuticktimer = SDL_GetTicks();

                            }
                            }

                        }
                        }
                        else if(optionmenu)
                    {
                        if(upflag==true || downflag==true)
                        {

                            if(currentick-menuticktimer > 200)
                            {
                            if(upflag==true &&downflag == false)
                            {
                                if(keybindselect>0){keybindselect -= 1;}
                                else{keybindselect = 14;}
                                menuticktimer = SDL_GetTicks();
                            }
                            else if(upflag == false && downflag == true)
                            {
                                if(keybindselect<14){keybindselect += 1;}
                                else{cmenubuttonflag = 0;}
                                menuticktimer = SDL_GetTicks();
                            }
                            }

                        }



                    }
                        else if(optionconfirmscreen)
                        {
                            if(leftflag==true || rightflag==true)
                            {

                                if(currentick-menuticktimer > 200)
                                {
                                if(leftflag==true && rightflag == false)
                                {
                                    if(coptionbuttonplace == 2){coptionbuttonplace -= 1;}
                                    else{coptionbuttonplace += 1;}
                                    menuticktimer = SDL_GetTicks();

                                }
                                else if(leftflag == false && rightflag == true)
                                {
                                    if(coptionbuttonplace == 2){coptionbuttonplace -= 1;}
                                    else{coptionbuttonplace += 1;}
                                    menuticktimer = SDL_GetTicks();

                                }
                                }

                            }
                            }







                    SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
                    SDL_RenderClear(gRenderer);

                    cmenubuttonstartrect.x = SCREEN_WIDTH*1/16;
                    cmenubuttonstartrect.y = SCREEN_HEIGHT*2/16;
                    cmenubuttonstartrect.w = 10+6*42;
                    cmenubuttonstartrect.h = 10+1*42;

                    cmenubuttonoptionsrect.x = SCREEN_WIDTH*1/16;
                    cmenubuttonoptionsrect.y = SCREEN_HEIGHT*4/16;
                    cmenubuttonoptionsrect.w = 10+7*42;
                    cmenubuttonoptionsrect.h = 10+1*42;

                    cmenubuttonquitrect.x = SCREEN_WIDTH*1/16;
                    cmenubuttonquitrect.y = SCREEN_HEIGHT*6/16;
                    cmenubuttonquitrect.w = 10+4*42;
                    cmenubuttonquitrect.h = 10+1*42;

                    quitmenurectconfirm.x = SCREEN_WIDTH*1/2+2*42;
                    quitmenurectconfirm.y = SCREEN_HEIGHT*1/2;
                    quitmenurectconfirm.w = 10+3*42;
                    quitmenurectconfirm.h = 10+1*42;

                    quitmenurectback.x = SCREEN_WIDTH*1/2-4*42-10;
                    quitmenurectback.y = SCREEN_HEIGHT*1/2;
                    quitmenurectback.w = 10+2*42;
                    quitmenurectback.h = 10+1*42;

                    pausemenurectconfirm.x = SCREEN_WIDTH*1/2+2*42;
                    pausemenurectconfirm.y = SCREEN_HEIGHT*1/2;
                    pausemenurectconfirm.w = 10+3*42;
                    pausemenurectconfirm.h = 10+1*42;

                    pausemenurectback.x = SCREEN_WIDTH*1/2-4*42-10;
                    pausemenurectback.y = SCREEN_HEIGHT*1/2;
                    pausemenurectback.w = 10+2*42;
                    pausemenurectback.h = 10+1*42;

                    for(int i=0;i<14;i++)
                    {
                    keybindinputrect[i].x = SCREEN_WIDTH*1/2-10*42-10;
                    keybindinputrect[i].y = SCREEN_HEIGHT/16-20+i*42;
                    keybindinputrect[i].w = 10+14*42 ;
                    keybindinputrect[i].h = 10+1*42;
                    }

                    keybindbackrect.x = SCREEN_WIDTH*1/2-10*42-10;
                    keybindbackrect.y = SCREEN_HEIGHT/16-20+15*42;
                    keybindbackrect.w = 10+4*42;
                    keybindbackrect.h = 10+1*42;

                    optionmenurectconfirm.x = SCREEN_WIDTH*1/2+2*42;
                    optionmenurectconfirm.y = SCREEN_HEIGHT*1/2;
                    optionmenurectconfirm.w = 10+3*42;
                    optionmenurectconfirm.h = 10+1*42;

                    optionmenurectback.x = SCREEN_WIDTH*1/2-4*42-10;
                    optionmenurectback.y = SCREEN_HEIGHT*1/2;
                    optionmenurectback.w = 10+2*42;
                    optionmenurectback.h = 10+1*42;




    if (gamemenu==true || quitmenu==true)
    {
        gamestart = false;
        gameplay = false;
        cbackgroundtexture.Render(0,0,0,gRenderer,SDL_FLIP_NONE);


        SDL_Rect fillRect = {0, 0, SCREEN_WIDTH*3/8, SCREEN_HEIGHT};
        SDL_SetRenderDrawColor(gRenderer,9,33,61,190);
        SDL_SetRenderDrawBlendMode(gRenderer,SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(gRenderer,&fillRect);

        SDL_Rect bannerRect = {10, 10, SCREEN_WIDTH*3/8-20, SCREEN_HEIGHT/16-20};
        SDL_SetRenderDrawColor(gRenderer,23,86,187,255);
        SDL_RenderFillRect(gRenderer,&bannerRect);

                    if(keylock && gamemenu == 1)
                    {
                        highlightcolor = {56,25,75};
                    }
                    else
                    {
                      highlightcolor = {34,108,255};
                    }


                    if( !cmenupathtext.LoadFromText("/Menu",font24,gRenderer,basecolor))
                    {
                        printf( "Unable to load player_a score text!\n" );
                    }
                    cmenupathtext.Render(10,10,0,gRenderer,SDL_FLIP_NONE);


                    if(cmenubuttonflag==1)
                    {
                        if( !cmenubuttonstarttext.LoadFromText("Start",font42,gRenderer,highlightcolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }

                        cmenubuttonstarttext.Render(10+SCREEN_WIDTH*1/16,10+SCREEN_HEIGHT*2/16,0,gRenderer,SDL_FLIP_NONE);
                        if(gameflag==true){gameplay = true;gamestart=true;gamemenu=false;};
                    }
                    else
                    {
                            if( !cmenubuttonstarttext.LoadFromText("Start",font42,gRenderer,basecolor))
                            {
                                printf( "Unable to load player_a score text!\n" );
                            }

                            cmenubuttonstarttext.Render(10+SCREEN_WIDTH*1/16,10+SCREEN_HEIGHT*2/16,0,gRenderer,SDL_FLIP_NONE);
                    }

                    if(cmenubuttonflag==2)
                    {
                        if( !cmenubuttonoptionstext.LoadFromText("Options",font42,gRenderer,highlightcolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        cmenubuttonoptionstext.Render(10+SCREEN_WIDTH*1/16,10+SCREEN_HEIGHT*4/16,0,gRenderer,SDL_FLIP_NONE);
                        if(optionflag==true){optionmenu = true; gamemenu = false;}


                    }
                    else
                    {
                        if( !cmenubuttonoptionstext.LoadFromText("Options",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        cmenubuttonoptionstext.Render(10+SCREEN_WIDTH*1/16,10+SCREEN_HEIGHT*4/16,0,gRenderer,SDL_FLIP_NONE);
                    }


                    if(cmenubuttonflag==3)
                    {
                        if( !cmenubuttonquittext.LoadFromText("Quit",font42,gRenderer,highlightcolor))
                        {
                            printf( "Unable to load player_a score text!\n" );

                        }
                        cmenubuttonquittext.Render(10+SCREEN_WIDTH*1/16,10+SCREEN_HEIGHT*6/16,0,gRenderer,SDL_FLIP_NONE);
                        if(quitflag==true){quitmenu = true;gamemenu=false;};



                    }
                    else
                    {
                        if( !cmenubuttonquittext.LoadFromText("Quit",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        cmenubuttonquittext.Render(10+SCREEN_WIDTH*1/16,10+SCREEN_HEIGHT*6/16,0,gRenderer,SDL_FLIP_NONE);
                    }



                    if(quitmenu)
                    {

                        if(keylock)
                        {
                            highlightcolor = {56,25,75};
                        }
                        else
                        {
                          highlightcolor = {34,108,255};
                        }




                        SDL_Rect fillRectquit = {SCREEN_WIDTH*1/2-4*42-10, SCREEN_HEIGHT*1/2-2*42-10, 9*42+10, 4*42+10};
                        SDL_SetRenderDrawColor(gRenderer,12,44,81,255);
                        SDL_SetRenderDrawBlendMode(gRenderer,SDL_BLENDMODE_BLEND);
                        SDL_RenderFillRect(gRenderer,&fillRectquit);

                        if( !quitqueestiontext.LoadFromText("Quit ?",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        quitqueestiontext.Render(SCREEN_WIDTH*1/2-2*42,SCREEN_HEIGHT*1/2-42-10,0,gRenderer,SDL_FLIP_NONE);

                        if(cquitbuttonplace==1)
                        {
                            if( !quitmenubuttonconfirm.LoadFromText("Yes",font42,gRenderer,highlightcolor))
                            {
                                printf( "Unable to load player_a score text!\n" );

                            }
                            quitmenubuttonconfirm.Render(SCREEN_WIDTH*1/2+2*42+10,SCREEN_HEIGHT*1/2,0,gRenderer,SDL_FLIP_NONE);
                            if(quitconfirm==true){quit = true;}
                        }
                        else
                        {
                            if( !quitmenubuttonconfirm.LoadFromText("Yes",font42,gRenderer,basecolor))
                            {
                                printf( "Unable to load player_a score text!\n" );
                            }
                            quitmenubuttonconfirm.Render(SCREEN_WIDTH*1/2+2*42+10,SCREEN_HEIGHT*1/2,0,gRenderer,SDL_FLIP_NONE);
                        }
                        if(cquitbuttonplace==2)
                        {
                            if( ! quitmenubuttonback.LoadFromText("No",font42,gRenderer,highlightcolor))
                            {
                                printf( "Unable to load player_a score text!\n" );

                            }
                             quitmenubuttonback.Render(SCREEN_WIDTH*1/2-4*42,SCREEN_HEIGHT*1/2,0,gRenderer,SDL_FLIP_NONE);
                            if(quitback==true){quitmenu = false;gamemenu=true;};



                        }
                        else
                        {
                            if( ! quitmenubuttonback.LoadFromText("No",font42,gRenderer,basecolor))
                            {
                                printf( "Unable to load player_a score text!\n" );
                            }
                             quitmenubuttonback.Render(SCREEN_WIDTH*1/2-4*42,SCREEN_HEIGHT*1/2,0,gRenderer,SDL_FLIP_NONE);
                        }






                    }



    }
    else if (gamepause == true)
    {
     cbackgroundtexture.Render(0,0,0,gRenderer,SDL_FLIP_NONE);
        if(gamepause)
        {

            if(keylock)
            {
                highlightcolor = {56,25,75};
            }
            else
            {
              highlightcolor = {34,108,255};
            }

            SDL_Rect fillRectquit = {SCREEN_WIDTH*1/2-7*42-10, SCREEN_HEIGHT*1/2-2*42-10, 14*42+20, 4*42+10};
            SDL_SetRenderDrawColor(gRenderer,12,44,81,255);
            SDL_SetRenderDrawBlendMode(gRenderer,SDL_BLENDMODE_BLEND);
            SDL_RenderFillRect(gRenderer,&fillRectquit);

            if( !pausequeestiontext.LoadFromText("Leave the Match ?",font42,gRenderer,basecolor))
            {
                printf( "Unable to load player_a score text!\n" );
            }
            pausequeestiontext.Render(SCREEN_WIDTH*1/2-7*42,SCREEN_HEIGHT*1/2-42-10,0,gRenderer,SDL_FLIP_NONE);


            if(cpausebuttonplace==1)
            {
                if( !pausemenubuttonconfirm.LoadFromText("Yes",font42,gRenderer,highlightcolor))
                {
                    printf( "Unable to load player_a score text!\n" );

                }
                pausemenubuttonconfirm.Render(SCREEN_WIDTH*1/2+2*42+10,SCREEN_HEIGHT*1/2,0,gRenderer,SDL_FLIP_NONE);
                if(pauseconfirm==true){gamepause = false;gamemenu = true;}
            }
            else
            {
                if( !pausemenubuttonconfirm.LoadFromText("Yes",font42,gRenderer,basecolor))
                {
                    printf( "Unable to load player_a score text!\n" );
                }
                pausemenubuttonconfirm.Render(SCREEN_WIDTH*1/2+2*42+10,SCREEN_HEIGHT*1/2,0,gRenderer,SDL_FLIP_NONE);
            }
            if(cpausebuttonplace==2)
            {
                if( ! pausemenubuttonback.LoadFromText("No",font42,gRenderer,highlightcolor))
                {
                    printf( "Unable to load player_a score text!\n" );

                }
                 pausemenubuttonback.Render(SCREEN_WIDTH*1/2-4*42,SCREEN_HEIGHT*1/2,0,gRenderer,SDL_FLIP_NONE);
                if(pauseback==true){gamepause = false;gameplay=true;};
            }
            else
            {
                if( ! pausemenubuttonback.LoadFromText("No",font42,gRenderer,basecolor))
                {
                    printf( "Unable to load player_a score text!\n" );
                }
                 pausemenubuttonback.Render(SCREEN_WIDTH*1/2-4*42,SCREEN_HEIGHT*1/2,0,gRenderer,SDL_FLIP_NONE);
            }






        }




    }
    else if (optionmenu == true || optionconfirmscreen == true || keybindcommand == true)
    {
        cbackgroundtexture.Render(0,0,0,gRenderer,SDL_FLIP_NONE);

        SDL_Rect bannerRect = {10, 10, SCREEN_WIDTH*3/8-20, SCREEN_HEIGHT/16-20};
        SDL_SetRenderDrawColor(gRenderer,23,86,187,255);
        SDL_RenderFillRect(gRenderer,&bannerRect);

        SDL_Rect optionfillrect = {SCREEN_WIDTH/2-10*42-20,SCREEN_HEIGHT/16-10,30+20*42,SCREEN_HEIGHT*15/16-20};
        SDL_SetRenderDrawColor(gRenderer,9,33,61,190);
        SDL_RenderFillRect(gRenderer,&optionfillrect);

                    if(keylock && optionmenu == 1)
                    {
                        highlightcolor = {56,25,75};
                    }
                    else
                    {
                      highlightcolor = {34,108,255};
                    }


                    if( !cmenupathtext.LoadFromText("/Menu/Options",font24,gRenderer,basecolor))
                    {
                        printf( "Unable to load player_a score text!\n" );
                    }
                    cmenupathtext.Render(10,10,0,gRenderer,SDL_FLIP_NONE);




    /* text pour chaque keybind */
                    if(keybindselect==0)
                    {
                        if( !keybindinputtext[0].LoadFromText("P1 Move Up",font42,gRenderer,highlightcolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                       keybindinputtext[0].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10,0,gRenderer,SDL_FLIP_NONE);
                       if(keybindactivate==0){keybindcommand=true;optionmenu=false;}
                    }
                    else
                    {
                        if( !keybindinputtext[0].LoadFromText("P1 Move Up",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        keybindinputtext[0].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10,0,gRenderer,SDL_FLIP_NONE);
                    }
                    if(keybindselect==1)
                    {
                        if( !keybindinputtext[1].LoadFromText("P1 Move Down",font42,gRenderer,highlightcolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                       keybindinputtext[1].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+42,0,gRenderer,SDL_FLIP_NONE);
                       if(keybindactivate==1){keybindcommand=true;optionmenu=false;}
                    }
                    else
                    {
                        if( !keybindinputtext[1].LoadFromText("P1 Move Down",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        keybindinputtext[1].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+42,0,gRenderer,SDL_FLIP_NONE);
                    }
                    if(keybindselect==2)
                    {
                        if( !keybindinputtext[2].LoadFromText("P1 Move Left",font42,gRenderer,highlightcolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                       keybindinputtext[2].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+2*42,0,gRenderer,SDL_FLIP_NONE);
                       if(keybindactivate==2){keybindcommand=true;optionmenu=false;}
                    }
                    else
                    {
                        if( !keybindinputtext[2].LoadFromText("P1 Move Left",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        keybindinputtext[2].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+2*42,0,gRenderer,SDL_FLIP_NONE);
                    }
                    if(keybindselect==3)
                    {
                        if( !keybindinputtext[3].LoadFromText("P1 Move Right",font42,gRenderer,highlightcolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                       keybindinputtext[3].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+3*42,0,gRenderer,SDL_FLIP_NONE);
                       if(keybindactivate==3){keybindcommand=true;optionmenu=false;}
                    }
                    else
                    {
                        if( !keybindinputtext[3].LoadFromText("P1 Move Right",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        keybindinputtext[3].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+3*42,0,gRenderer,SDL_FLIP_NONE);
                    }
                    if(keybindselect==4)
                    {
                        if( !keybindinputtext[4].LoadFromText("P1 Shoot Gun",font42,gRenderer,highlightcolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                       keybindinputtext[4].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+4*42,0,gRenderer,SDL_FLIP_NONE);
                        if(keybindactivate==4){keybindcommand=true;optionmenu=false;}
                    }
                    else
                    {
                        if( !keybindinputtext[4].LoadFromText("P1 Shoot Gun",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        keybindinputtext[4].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+4*42,0,gRenderer,SDL_FLIP_NONE);
                        if(keybindactivate==4){keybindcommand=true;optionmenu=false;}
                    }
                    if(keybindselect==5)
                    {
                        if( !keybindinputtext[5].LoadFromText("P1 Use Knife",font42,gRenderer,highlightcolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                       keybindinputtext[5].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+5*42,0,gRenderer,SDL_FLIP_NONE);
                       if(keybindactivate==5){keybindcommand=true;optionmenu=false;}
                    }
                    else
                    {
                        if( !keybindinputtext[5].LoadFromText("P1 Use Knife",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        keybindinputtext[5].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+5*42,0,gRenderer,SDL_FLIP_NONE);
                    }
                    if(keybindselect==6)
                    {
                        if( !keybindinputtext[6].LoadFromText("P1 Use Special",font42,gRenderer,highlightcolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                       keybindinputtext[6].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+6*42,0,gRenderer,SDL_FLIP_NONE);
                       if(keybindactivate==6){keybindcommand=true;optionmenu=false;}
                    }
                    else
                    {
                        if( !keybindinputtext[6].LoadFromText("P1 Use Special",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        keybindinputtext[6].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+6*42,0,gRenderer,SDL_FLIP_NONE);
                    }
                    if(keybindselect==7)
                    {
                        if( !keybindinputtext[7].LoadFromText("P2 Move Up",font42,gRenderer,highlightcolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                       keybindinputtext[7].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+7*42,0,gRenderer,SDL_FLIP_NONE);
                       if(keybindactivate==7){keybindcommand=true;optionmenu=false;}
                    }
                    else
                    {
                        if( !keybindinputtext[7].LoadFromText("P2 Move Up",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        keybindinputtext[7].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+7*42,0,gRenderer,SDL_FLIP_NONE);
                    }

                    if(keybindselect==8)
                    {
                        if( !keybindinputtext[8].LoadFromText("P2 Move Down",font42,gRenderer,highlightcolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                       keybindinputtext[8].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+8*42,0,gRenderer,SDL_FLIP_NONE);
                       if(keybindactivate==8){keybindcommand=true;optionmenu=false;}
                    }
                    else
                    {
                        if( !keybindinputtext[8].LoadFromText("P2 Move Down",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        keybindinputtext[8].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+8*42,0,gRenderer,SDL_FLIP_NONE);
                    }
                    if(keybindselect==9)
                    {
                        if( !keybindinputtext[9].LoadFromText("P2 Move Left",font42,gRenderer,highlightcolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                       keybindinputtext[9].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+9*42,0,gRenderer,SDL_FLIP_NONE);
                       if(keybindactivate==9){keybindcommand=true;optionmenu=false;}
                    }
                    else
                    {
                        if( !keybindinputtext[9].LoadFromText("P2 Move Left",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        keybindinputtext[9].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+9*42,0,gRenderer,SDL_FLIP_NONE);
                    }
                    if(keybindselect==10)
                    {
                        if( !keybindinputtext[10].LoadFromText("P2 Move Right",font42,gRenderer,highlightcolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                       keybindinputtext[10].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+10*42,0,gRenderer,SDL_FLIP_NONE);
                       if(keybindactivate==10){keybindcommand=true;optionmenu=false;}
                    }
                    else
                    {
                        if( !keybindinputtext[10].LoadFromText("P2 Move Right",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        keybindinputtext[10].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+10*42,0,gRenderer,SDL_FLIP_NONE);
                    }
                    if(keybindselect==11)
                    {
                        if( !keybindinputtext[11].LoadFromText("P1 Shoot Gun",font42,gRenderer,highlightcolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                       keybindinputtext[11].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+11*42,0,gRenderer,SDL_FLIP_NONE);
                       if(keybindactivate==11){keybindcommand=true;optionmenu=false;}
                    }
                    else
                    {
                        if( !keybindinputtext[11].LoadFromText("P2 Shoot Gun",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        keybindinputtext[11].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+11*42,0,gRenderer,SDL_FLIP_NONE);
                    }
                    if(keybindselect==12)
                    {
                        if( !keybindinputtext[12].LoadFromText("P2 Use Knife",font42,gRenderer,highlightcolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                       keybindinputtext[12].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+12*42,0,gRenderer,SDL_FLIP_NONE);
                       if(keybindactivate==12){keybindcommand=true;optionmenu=false;}
                    }
                    else
                    {
                        if( !keybindinputtext[12].LoadFromText("P2 Use Knife",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        keybindinputtext[12].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+12*42,0,gRenderer,SDL_FLIP_NONE);
                    }
                    if(keybindselect==13)
                    {
                        if( !keybindinputtext[13].LoadFromText("P2 Use Special",font42,gRenderer,highlightcolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                       keybindinputtext[13].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+13*42,0,gRenderer,SDL_FLIP_NONE);
                       if(keybindactivate==13){keybindcommand=true;optionmenu=false;}
                    }
                    else
                    {
                        if( !keybindinputtext[13].LoadFromText("P2 Use Special",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        keybindinputtext[13].Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+13*42,0,gRenderer,SDL_FLIP_NONE);
                    }

                    if(keybindselect==14)
                    {
                        if( !keybindbacktext.LoadFromText("Back",font42,gRenderer,highlightcolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                       keybindbacktext.Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+15*42,0,gRenderer,SDL_FLIP_NONE);
                       if(keybindactivate==14){
                           if(keybindchange)
                           {
                               optionmenu = false; optionconfirmscreen = true;
                           }
                           else
                           {
                           optionmenu=false;gamemenu=true;
                                }

                       }
                    }
                    else
                    {
                        if( !keybindbacktext.LoadFromText("Back",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        keybindbacktext.Render(SCREEN_WIDTH/2-10*42-10,SCREEN_HEIGHT/16-10+15*42,0,gRenderer,SDL_FLIP_NONE);
                    }

                    for(int i =0; i<14;i++)
                    {
                    textkeybindbuffer.str("");
                    if(keyvalue[i]!=NULL)
                    {
                     textkeybindbuffer << SDL_GetKeyName(keyvalue[i]);
                    }
                    else
                    {
                     textkeybindbuffer << "EMPTY";
                    }
                    if( !keybindoutputtext[i].LoadFromText( textkeybindbuffer.str().c_str(),font42,gRenderer,{56,148,225}))
                    {
                        printf( "Unable to load player_a score text!\n" );
                    }
                    keybindoutputtext[i].Render(SCREEN_WIDTH/2+3*42-10,SCREEN_HEIGHT/16-10+i*42,0,gRenderer,SDL_FLIP_NONE);
    }

                    if(optionconfirmscreen)
                    {

                        if(keylock)
                        {
                            highlightcolor = {56,25,75};
                        }
                        else
                        {
                          highlightcolor = {34,108,255};
                        }




                        SDL_Rect fillRectoption = {SCREEN_WIDTH*1/2-4*42-20, SCREEN_HEIGHT*1/2-3*42-10, 9*42+20, 5*42+10};
                        SDL_SetRenderDrawColor(gRenderer,12,44,81,255);
                        SDL_SetRenderDrawBlendMode(gRenderer,SDL_BLENDMODE_BLEND);
                        SDL_RenderFillRect(gRenderer,&fillRectoption);

                        if( !pausequeestiontext.LoadFromText("Save Change",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        pausequeestiontext.Render(SCREEN_WIDTH*1/2-4*42-10,SCREEN_HEIGHT*1/2-3*42-10,0,gRenderer,SDL_FLIP_NONE);
                        if( !pausequeestiontextb.LoadFromText("and Quit ?",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        pausequeestiontextb.Render(SCREEN_WIDTH*1/2-4*42+20,SCREEN_HEIGHT*1/2-2*42-10,0,gRenderer,SDL_FLIP_NONE);

                        if(coptionbuttonplace==1)
                        {
                            if( !pausemenubuttonconfirm.LoadFromText("Yes",font42,gRenderer,highlightcolor))
                            {
                                printf( "Unable to load player_a score text!\n" );

                            }
                            pausemenubuttonconfirm.Render(SCREEN_WIDTH*1/2+2*42+10,SCREEN_HEIGHT*1/2,0,gRenderer,SDL_FLIP_NONE);
                            if(optionconfirm==true){optionconfirmscreen = false;gamemenu=true;savefile(keyvalue);}
                        }
                        else
                        {
                            if( !pausemenubuttonconfirm.LoadFromText("Yes",font42,gRenderer,basecolor))
                            {
                                printf( "Unable to load player_a score text!\n" );
                            }
                            pausemenubuttonconfirm.Render(SCREEN_WIDTH*1/2+2*42+10,SCREEN_HEIGHT*1/2,0,gRenderer,SDL_FLIP_NONE);
                        }

                        if(coptionbuttonplace==2)
                        {
                            if( ! pausemenubuttonback.LoadFromText("No",font42,gRenderer,highlightcolor))
                            {
                                printf( "Unable to load player_a score text!\n" );

                            }
                             pausemenubuttonback.Render(SCREEN_WIDTH*1/2-4*42,SCREEN_HEIGHT*1/2,0,gRenderer,SDL_FLIP_NONE);
                            if(optionback==true){
                                optionconfirmscreen = false; gamemenu=true;

                                keyvalue[0] = loadfile(0);
                                keyvalue[1] = loadfile(1);
                                keyvalue[2] = loadfile(2);
                                keyvalue[3] = loadfile(3);
                                keyvalue[4] = loadfile(4);
                                keyvalue[5] = loadfile(5);
                                keyvalue[6] = loadfile(6);
                                keyvalue[7] = loadfile(7);
                                keyvalue[8] = loadfile(8);
                                keyvalue[9] = loadfile(9);
                                keyvalue[10] = loadfile(10);
                                keyvalue[11] = loadfile(11);
                                keyvalue[12] = loadfile(12);
                                keyvalue[13] = loadfile(13);




                            };



                        }
                        else
                        {
                            if( ! pausemenubuttonback.LoadFromText("No",font42,gRenderer,basecolor))
                            {
                                printf( "Unable to load player_a score text!\n" );
                            }
                             pausemenubuttonback.Render(SCREEN_WIDTH*1/2-4*42,SCREEN_HEIGHT*1/2,0,gRenderer,SDL_FLIP_NONE);
                        }




    }
                    if(keybindcommand)
                    {
                        SDL_Rect keybindcommandrect = {SCREEN_WIDTH*1/2-7*42-10, SCREEN_HEIGHT*1/2-2*42-30, 14*42+30, 3*42+10};
                        SDL_SetRenderDrawColor(gRenderer,12,44,81,255);
                        SDL_SetRenderDrawBlendMode(gRenderer,SDL_BLENDMODE_BLEND);
                        SDL_RenderFillRect(gRenderer,&keybindcommandrect);

                        if( !keybindcommandtext.LoadFromText("Press new key",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        keybindcommandtext.Render(SCREEN_WIDTH*1/2-5*42-10,SCREEN_HEIGHT*1/2-2*42-10,0,gRenderer,SDL_FLIP_NONE);
                        if( !keybindcommandtext.LoadFromText("or escape to back",font42,gRenderer,basecolor))
                        {
                            printf( "Unable to load player_a score text!\n" );
                        }
                        keybindcommandtext.Render(SCREEN_WIDTH*1/2-7*42,SCREEN_HEIGHT*1/2-42-10,0,gRenderer,SDL_FLIP_NONE);


                    }


    }







                 //   SDL_Rect fillRectb = {SCREEN_WIDTH*3/8, 0, SCREEN_WIDTH*5/8, SCREEN_HEIGHT};
                 //   SDL_SetRenderDrawColor(gRenderer,12,44,81,190);
                 //   SDL_SetRenderDrawBlendMode(gRenderer,SDL_BLENDMODE_BLEND);
                 //   SDL_RenderFillRect(gRenderer,&fillRectb);
                                   }
                else if(gameplay)
                {
                    gamemenu = false;

                    cbackgroundtexture.Render(0,0,0,gRenderer,SDL_FLIP_NONE);
                  if(gamestart)
                  {
                      playera.SetBind(0, keyvalue[0]);
                      playera.SetBind(1, keyvalue[1]);
                      playera.SetBind(2, keyvalue[2]);
                      playera.SetBind(3, keyvalue[3]);
                      playera.SetBind(4, keyvalue[4]);
                      playera.SetBind(5, keyvalue[5]);
                      playera.SetBind(6, keyvalue[6]);
                      playerb.SetBind(0, keyvalue[7]);
                      playerb.SetBind(1, keyvalue[8]);
                      playerb.SetBind(2, keyvalue[9]);
                      playerb.SetBind(3, keyvalue[10]);
                      playerb.SetBind(4, keyvalue[11]);
                      playerb.SetBind(5, keyvalue[12]);
                      playerb.SetBind(6, keyvalue[13]);
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
                  gamestart= false;
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
                if( !playerascoretext.LoadFromText(textbuffer.str().c_str(),font42,gRenderer,{25,75,144}))
                {
                    printf( "Unable to load player_a score text!\n" );
                }
                    textbuffer.str("");
                    textbuffer << playerbscore ;
                    if( !playerbscoretext.LoadFromText(textbuffer.str().c_str(),font42,gRenderer,{25,75,144}))
                    {
                        printf( "Unable to load player_b score text!\n" );
                    }
                    textbuffer.str("");
                    textbuffer << playera.GetAmmunition();
                    if( !playerabulletstext.LoadFromText(textbuffer.str().c_str(),font42,gRenderer,{25,75,144}))
                    {
                        printf( "Unable to load player_a bullets text!\n" );
                    }
                    textbuffer.str("");
                    textbuffer << playerb.GetAmmunition() ;
                    if( !playerbbulletstext.LoadFromText(textbuffer.str().c_str(),font42,gRenderer,{25,75,144}))
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

              if(checkcollision(playera.m_playercharacter.GetStabRect(),ccharacter[i].GetRect())){ccharacter[i].SetAlive(0);}
            }
            if(checkcollision(playera.m_playercharacter.GetStabRect(),playerb.m_playercharacter.GetRect())){playerb.m_playercharacter.SetAlive(0);}

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

          if(checkcollision(playerb.m_playercharacter.GetStabRect(),ccharacter[i].GetRect())){ccharacter[i].SetAlive(0);}
        }
        if(checkcollision(playerb.m_playercharacter.GetStabRect(),playera.m_playercharacter.GetRect())){playera.m_playercharacter.SetAlive(0);}

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


playerascoretext.Render(2*24,2,0,gRenderer,SDL_FLIP_NONE);
playerabulletstext.Render(1./10*SCREEN_WIDTH+2*24,2,0,gRenderer,SDL_FLIP_NONE);
playerbbulletstext.Render(9./10*SCREEN_WIDTH-2*24,2,0,gRenderer,SDL_FLIP_NONE);
playerbscoretext.Render(SCREEN_WIDTH-2*24,2,0,gRenderer,SDL_FLIP_NONE);
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
                              textbuffer << "Player " << iswinner  << " Win !";
                              if( !winnertext.LoadFromText(textbuffer.str().c_str(),font42,gRenderer,{25,75,144}))
                              {
                                  printf( "Unable to load player_a score text!\n" );
                              }
                              winnertext.Render((1./2)*(SCREEN_WIDTH-winnertext.GetWidth()),1./10*SCREEN_HEIGHT,0,gRenderer,SDL_FLIP_NONE);
                              textbuffer.str("");
                              textbuffer << "New Game Starts in : "<< dticktimer/1000;
                              if( !winnertext.LoadFromText(textbuffer.str().c_str(),font42,gRenderer,{25,75,144}))
                              {
                                  printf( "Unable to load player_a score text!\n" );
                              }
                              winnertext.Render((1./2)*(SCREEN_WIDTH-winnertext.GetWidth()),1./10*SCREEN_HEIGHT+42,0,gRenderer,SDL_FLIP_NONE);







                          }
                       }
                       else
                       {
                       gamestart = true;
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








//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA



