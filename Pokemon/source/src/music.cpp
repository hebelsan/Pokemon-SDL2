#include "music.hpp"
#include <SDL2/SDL.h>

Music::Music() {
	int flags = MIX_INIT_MP3;
	int result = 0;
	//Initialize SDL_mixer
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{
		printf("Failed to open audio mix\n");
	}
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		printf("Failed to init SDL\n");
		exit(1);
	}
	if (flags != (result = Mix_Init(flags))) {
		printf("Could not initialize mixer (result: %d).\n", result);
		printf("Mix_Init: %s\n", Mix_GetError());
	    exit(1);
	}
	this->_music = NULL;
}

Music::~Music() {
	Mix_FreeMusic(this->_music);
	Mix_CloseAudio();
}

void Music::loadMusicFile(std::string fileName) {
	this->_music = Mix_LoadMUS(fileName.c_str());
}

void Music::play(int loops) {
	Mix_PlayMusic(this->_music, loops);
}

void Music::playIfReady(int loops) {
	if (this->isPlaying() == 0) {
		this->play(loops);
	}
}

void Music::pause() {
	Mix_PauseMusic();
}

void Music::resume() {
	Mix_ResumeMusic();
}

// returns 0 if none is playing
int Music::isPlaying() {
	return Mix_PlayingMusic();
}

void Music::fadeIn(int loops, int milliSek) {
	Mix_FadeInMusic(this->_music, loops, milliSek);
}

// if channel is -1 all channels are faded out
void Music::fadeOut(int milliSec) {
	Mix_FadeOutMusic(milliSec);
}





