#include "mySDL.h"
#include <iostream>
#include <string>
#include <SDL2/SDL_mixer.h>

using namespace std;

static int step = 2;

static int testThread(void *ptr)
{
	bool* quit = (bool*)ptr;
	while(true)
	{
		cout<<"子线程"<<endl;
		SDL_Delay(2000);
		if(*quit)
		{
			break;
		}
	}
	return 0;
}

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Font* ttf = initTtf((char*)"Vera.ttf");
	SDL_Window* win = SDL_CreateWindow((char*)"Game",SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,600,400,
										SDL_WINDOW_SHOWN);
	SDL_Renderer* rend = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
	
	SDL_RenderClear(rend);
	Image person((char*)"person.jpg",rend);
	person.setImagePosition(10,10);
	person.setImagesize(20,20);
	person.presentImage(rend);
	SDL_RenderPresent(rend);

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,4086);
	Mix_Music* music = Mix_LoadMUS((char*)"music.wav");
	Mix_Chunk* chunk = Mix_LoadWAV((char*)"alert.wav");
	Mix_PlayMusic(music,1000);

	bool quitTread = false;
	SDL_Thread* thread = SDL_CreateThread(testThread,"child",(void*)&quitTread);

	SDL_Event event;
    bool quit = false;
	bool flag = false;
	SDL_Rect fontRect = {10,10,100,20};
	SDL_Color color = {255,0,0,0};
    while(!quit)
	{
		//while(SDL_PollEvent(&event))
		if(SDL_WaitEvent(&event))
		{
			if(event.type==SDL_QUIT)
			{
				quit=true;
			}
			else if(event.type==SDL_KEYDOWN)
			{
				Mix_PlayChannel(-1,chunk,1);
				switch(event.key.keysym.sym)
				{
					case SDLK_UP: person.moveUp(step); break;
					case SDLK_DOWN: person.moveDown(step); break;
					case SDLK_RIGHT: person.moveRight(step); break;
					case SDLK_LEFT: person.moveLeft(step); quitTread = true; break;
				}
				//SDL_WaitThread(thread,NULL);
				SDL_RenderClear(rend);
				person.presentImage(rend);
				fontRect.x += step;
				fontRect.y += step;
				showTtf(ttf,rend,&fontRect,&color,(char*)"我爱你!");
				flag = true;
			}
	    }
		if(flag)
		{
			SDL_RenderPresent(rend);
			flag = false;
		}
		SDL_Delay(5);
	}
	Mix_FreeMusic(music);
	Mix_FreeChunk(chunk);
	closeTtf(ttf);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}