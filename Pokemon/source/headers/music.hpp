/*
 * music.hpp
 *
 */

#ifndef MUSIC_HPP_
#define MUSIC_HPP_


#include "SDL2/SDL_mixer.h"
#include <string>

class Music {
public:
	static Music* getInstance();
	void loadMusicFile(std::string fileName);
	void play(int loops);
	void playIfReady(int loops);
	void pause();
	void resume();
	int isPlaying();
	void fadeIn(int loops, int milliSek);
	void fadeOut(int milliSec);
private:
	static Music* _instance;
	Music();
	Music( const Music& );
	~Music();
	Mix_Music* _music;
};



#endif /* MUSIC_HPP_ */
