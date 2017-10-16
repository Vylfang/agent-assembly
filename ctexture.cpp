#include "ctexture.h"

CTexture::CTexture()
{
    m_texture = NULL;
    m_width = 0;
    m_height = 0;
}

CTexture::~CTexture()
{
    Free();
}

bool CTexture::LoadFromFile( std::string path , SDL_Renderer* gRenderer)
{
    Free();

    SDL_Texture* temptexture = NULL;
    SDL_Surface* loadedsurface = IMG_Load( path.c_str());

    if( loadedsurface == NULL ){printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );}
    else
    {
        //Color key image (Green)
        SDL_SetColorKey( loadedsurface, SDL_TRUE, SDL_MapRGB( loadedsurface->format, 0, 0xFF, 0 ) );

        //Create texture from surface pixels
        temptexture = SDL_CreateTextureFromSurface( gRenderer, loadedsurface );
        if( temptexture == NULL ){printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );}
        else
        {
            //Get image dimensions
            m_width = loadedsurface->w;
            m_height = loadedsurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedsurface );
    }

    //Return success
    m_texture = temptexture;
    return m_texture != NULL;
}

bool CTexture::LoadFromText( std::string text, TTF_Font* gFont, SDL_Renderer* gRenderer, SDL_Color textcolor)
{
    Free();
    //SDL_Color textcolor = {0,0,0};
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textcolor);

    if(textSurface == NULL){printf("Unable to render text surface ! SDL_ttf Error: %s\n", TTF_GetError());}
    else
    {
    m_texture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if(m_texture == NULL){printf("Unable to create texture from rendered text! SDL_Error: %s\n",SDL_GetError());}
    else
    {
        m_width = textSurface->w;
        m_height = textSurface->h;

    }

    SDL_FreeSurface(textSurface);
    }

    return m_texture !=NULL;
}


void CTexture::Free()
{
    //Free texture if it exists
    if( m_texture != NULL )
    {
        SDL_DestroyTexture( m_texture );
        m_texture = NULL;
        m_width = 0;
        m_height = 0;
    }
}

void CTexture::SetColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( m_texture, red, green, blue );
}

void CTexture::SetAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( m_texture, alpha );
}

void CTexture::Render( int x, int y, SDL_Rect* clip , SDL_Renderer* gRenderer, SDL_RendererFlip flip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, m_width, m_height };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( gRenderer, m_texture, clip, &renderQuad, 0, NULL, flip );
}

int CTexture::GetWidth()
{
    return m_width;
}

int CTexture::GetHeight()
{
    return m_height;
}

