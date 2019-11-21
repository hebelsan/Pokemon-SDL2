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
		int coinRand = (rand() % 4) + 1; // number 1 <= x <= 4

		if(coinRand <= 2) {
			return true;
		} else {
			return false;
		}
	}

	// calculates a number for battle,  indem von 100 eine zufällige Zahl zwischen 0 und 15 abgezogen wird
	static int calculateZ() {
		struct timespec ts;
		clock_gettime(CLOCK_MONOTONIC, &ts);
		srand((time_t)ts.tv_nsec);
		int randNumber = (rand() % 16); // number 0 <= x <= 15

		return (100 - randNumber);
	}
};



#endif /* RANDOM_HPP_ */
