/*
 * PokemonTypeConverter.hpp
 *
 *  Created on: 24.04.2018
 *      Author: Alexander
 */

#ifndef POKEMONTYPECONVERTER_HPP_
#define POKEMONTYPECONVERTER_HPP_

#include <string>
#include "globals.hpp"

class PokemonTypeConverter {
public:
	static std::string pokemonTypToString(PokemonTyp typ) {
		switch(typ) {
			case PokemonTyp::NORMAL:
				return "Normal";
				break;
			case PokemonTyp::KAMPF:
				return "Kampf";
				break;
			case PokemonTyp::FLUG:
				return "Flug";
				break;
			case PokemonTyp::GIFT:
				return "Gift";
				break;
			case PokemonTyp::BODEN:
				return "Boden";
				break;
			case PokemonTyp::GESTEIN:
				return "Gestein";
				break;
			case PokemonTyp::KAEFER:
				return "Kaefer";
				break;
			case PokemonTyp::GEIST:
				return "Geist";
				break;
			case PokemonTyp::STAHL:
				return "Stahl";
				break;
			case PokemonTyp::FEUER:
				return "Feuer";
				break;
			case PokemonTyp::WASSER:
				return "Wasser";
				break;
			case PokemonTyp::PFLANZE:
				return "Pflanze";
				break;
			case PokemonTyp::ELEKTRO:
				return "Elektro";
				break;
			case PokemonTyp::PSYCHO:
				return "Psycho";
				break;
			case PokemonTyp::EIS:
				return "Eis";
				break;
			case PokemonTyp::DRACHE:
				return "Drache";
				break;
			case PokemonTyp::UNLICHT:
				return "Unlicht";
				break;
		}
	}
private:
};



#endif /* POKEMONTYPECONVERTER_HPP_ */
