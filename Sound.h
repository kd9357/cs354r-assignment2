#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>

class Sound
{
	public:
		Mix_Chunk *score;
		Mix_Chunk *whoosh;
		Mix_Chunk *bounce;

		int success;

		Sound();
		~Sound();
};