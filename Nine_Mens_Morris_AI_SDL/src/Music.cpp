#include "Music.h"
#include "SDL/SDL_mixer.h"

void music(char nomDemusic[20])
{  int init = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) ;
   Mix_Music *musique;
   musique = Mix_LoadMUS(nomDemusic);
   //Mix_PlayChannel(-1, musique, 0);
   int play = Mix_PlayMusic(musique, -1);

   Mix_FreeMusic(musique);
   Mix_CloseAudio();
}


