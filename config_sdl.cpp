#include<iostream>
#include<ctime>
#include "config_sdl.h"

using namespace std;

extern "C" FILE* __cdecl __iob_func()
{
	struct _iobuf_VS2012 { // ...\Microsoft Visual Studio 11.0\VC\include\stdio.h #56
		char *_ptr;
		int   _cnt;
		char *_base;
		int   _flag;
		int   _file;
		int   _charbuf;
		int   _bufsiz;
		char *_tmpfname;
	};
	// VS2015 has only FILE = struct {void*}

	int const count = sizeof(_iobuf_VS2012) / sizeof(FILE);

	//// stdout
	//return (FILE*)(&(__acrt_iob_func(1)->_Placeholder) - count);

	// stderr
	return (FILE*)(&(__acrt_iob_func(2)->_Placeholder) - 2 * count);
}

 
SDL_Texture *loadText(SDL_Renderer* render,const char *text, SDL_Color coul, TTF_Font* font2){
	//on crée une surface à partir du texte
	SDL_Surface*surface=TTF_RenderText_Solid(font2,text,coul);
	//on crée une texture à partir de la surface
	SDL_Texture*texture=SDL_CreateTextureFromSurface(render,surface);
	SDL_FreeSurface(surface);
	return texture;
}

