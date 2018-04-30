/*
 * random.hpp
 *
 *  Created on: 01.05.2018
 *      Author: Alexander
 */

#ifndef RANDOM_HPP_
#define RANDOM_HPP_

#include <time.h>
#include <stdlib.h>

class Random {
public:
	static bool flipCoin() {
		struct timespec ts;
		clock_gettime(CLOCK_MONOTONIC, &ts);
		srand((time_t)ts.tv_nsec);
		int dvRand = (rand() % 31) + 1;
		int sexRand = (rand() % 4) + 1; // number 1 <= x <= 4

		if(sexRand <= 2) {
			return true;
		} else {
			return false;
		}
	}
};



#endif /* RANDOM_HPP_ */
