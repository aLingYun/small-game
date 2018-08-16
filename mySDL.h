#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Image
{
private:
    uint x;
    uint y;
    uint w;
    uint h;
    SDL_Surface* surface;
    SDL_Texture* texture;
public:
    Image(char* filename, SDL_Renderer* rend);
    ~Image();
    void setImagesize(uint nw, uint nh);
    void setImagePosition(uint nx, uint ny);
    void presentImage(SDL_Renderer* rend);
    void moveUp(int pos);
    void moveDown(int pos);
    void moveRight(int pos);
    void moveLeft(int pos);
};

TTF_Font* initTtf(char* ttfPath);
void showTtf(TTF_Font* ttf,SDL_Renderer* rend,SDL_Rect* rect,SDL_Color* color,char* str);
void closeTtf(TTF_Font* ttf);