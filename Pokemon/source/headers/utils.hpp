/*
 * utils.hpp
 *
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <string>
#include <vector>


class Utils {
public:

	// unsigned int split
	// splits a string <txt> everywhere a certain character <ch> is found
	// stores the resulting substring in a vector <strs>
	// returns the size of the vector
	// 25,30,2,17 -> [25, 30, 2, 7]
	static unsigned int split(const std::string &txt, std::vector<std::string> &strs, char ch) {
		unsigned int pos = txt.find(ch);
		int initialPos = 0;
		strs.clear();
		while (pos != std::string::npos) {
			strs.push_back(txt.substr(initialPos, pos - initialPos + 1));
			initialPos = pos + 1;

			pos = txt.find(ch, initialPos);
		}
		// ADD the last one
		strs.push_back(txt.substr(initialPos, std::min<int>(pos, txt.size() - (initialPos + 1))));

		return strs.size();
	}
};


#endif /* UTILS_HPP_ */
