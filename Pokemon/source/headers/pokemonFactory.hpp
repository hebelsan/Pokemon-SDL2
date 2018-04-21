/*
 * pokemonFactory.hpp
 *
 *  Created on: 15.04.2018
 *      Author: Alexander
 */

#ifndef POKEMONFACTORY_HPP_
#define POKEMONFACTORY_HPP_

#include <string>
#include "pokemon.hpp"

class PokemonFactory {
public:
	static Pokemon createPokemon(std::string name, int level);
	static std::vector<Pokemon> createPokemonsFromString(std::string);
};



#endif /* POKEMONFACTORY_HPP_ */
