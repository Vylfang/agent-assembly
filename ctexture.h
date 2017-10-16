#ifndef CTEXTURE_H
#define CTEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

class CTexture
{
    public:
        //Initializes variables
        CTexture();

        //Deallocates memory
        ~CTexture();

        //Loads image at specified path
        bool LoadFromFile(std::string path , SDL_Renderer* gRenderer = NULL);
        bool LoadFromText(std::string text, TTF_Font* gFont = NULL, SDL_Renderer* gRenderer = NULL, SDL_Color textcolor={0,0,0});

        //Deallocates texture
        void Free();

        //Set color modulation
        void SetColor( Uint8 red, Uint8 green, Uint8 blue );

        //Set alpha modulation
        void SetAlpha( Uint8 alpha );

        //Renders texture at given point
        void Render( int x, int y, SDL_Rect* clip = NULL , SDL_Renderer* gRenderer = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

        //Gets image dimensions
        int GetWidth();
        int GetHeight();

    private:
        //The actual hardware texture
        SDL_Texture *m_texture;

        //Image dimensions
        int m_width;
        int m_height;
};

#endif // CTEXTURE_H
