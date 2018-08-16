#include "mySDL.h"


Image::Image(char* filename,SDL_Renderer* rend)
{
    surface = IMG_Load(filename);
    if(surface == NULL)
    {
        return;
    }
    texture = SDL_CreateTextureFromSurface(rend,surface);
}

Image::~Image()
{
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Image::setImagesize(uint nw, uint nh)
{
    w = nw;
    h = nh;
}
    
void Image::setImagePosition(uint nx, uint ny)
{
    x = nx;
    y = ny;
}

void Image::presentImage(SDL_Renderer* rend)
{
    SDL_Rect rect = {(int)x,(int)y,(int)w,(int)h};
    //SDL_RenderClear(rend);
    SDL_RenderCopyEx(rend,texture,NULL,&rect,0,0,SDL_FLIP_NONE);
    //SDL_RenderPresent(rend);
}

void Image::moveUp(int pos)
{
    y -= pos;
}

void Image::moveDown(int pos)
{
    y += pos;
}

void Image::moveLeft(int pos)
{
    x -= pos;
}

void Image::moveRight(int pos)
{
    x += pos;
}

TTF_Font* initTtf(char* ttfPath)
{
    TTF_Init();
    TTF_Font* ttf = TTF_OpenFont(ttfPath,100);
    return ttf;
}

void showTtf(TTF_Font* ttf,SDL_Renderer* rend,SDL_Rect* rect,SDL_Color* color,char* str)
{
    SDL_Surface* surface = TTF_RenderUTF8_Blended(ttf,str,*color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rend,surface);
    SDL_RenderCopy(rend,texture,NULL,rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void closeTtf(TTF_Font* ttf)
{
    TTF_CloseFont(ttf);
    TTF_Quit();
}