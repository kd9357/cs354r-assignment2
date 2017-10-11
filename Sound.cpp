#include "Sound.h"

Sound::Sound()
{
	if(SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		std::cout << "SDL could not be initialized. SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	}

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512) < 0)
	{
		std::cout << "SDL_mixer could not be initialized. SDL_mixer Error: " << Mix_GetError() << std::endl;
		success = false;
	}

	score = Mix_LoadWAV("assets/Whoosh.mp3");
	whoosh = Mix_LoadWAV("assets/Whoosh.mp3");
	bounce = Mix_LoadWAV("assets/bounce.wav");
}
