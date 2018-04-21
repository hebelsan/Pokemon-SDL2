#include "pokemonFactory.hpp"
#include <iostream>

std::vector<Pokemon> PokemonFactory::createPokemonsFromString(std::string pokemonsString) {
	std::vector<Pokemon> pokemons;
	std::vector<std::string> singlePokemons;
	std::string delimiterPokemon = ":";
	std::string delimiterLevel = ",";

	size_t pos = 0;
	std::string section;
	while ((pos = pokemonsString.find(delimiterPokemon)) != std::string::npos) {
		section = pokemonsString.substr(0, pos);
		singlePokemons.push_back(section);
		pokemonsString.erase(0, pos + delimiterPokemon.length());
	}
	singlePokemons.push_back(pokemonsString);

	for(unsigned int i = 0; i < singlePokemons.size(); i++) {
		pos = singlePokemons.at(i).find(delimiterLevel);
		std::string pokemonName = singlePokemons.at(i).substr(0, pos);
		std::string pokemonLevelString = singlePokemons.at(i).substr(pos + delimiterPokemon.length(), singlePokemons.at(i).length() - 1);
		int pokemonLevel = atoi( pokemonLevelString.c_str() );
		pokemons.push_back(createPokemon(pokemonName, pokemonLevel));
	}

	return pokemons;
}

Pokemon PokemonFactory::createPokemon(std::string name, int level) {
	if (name == "endivie") {
		return Endivie(level);
	} else if (name == "feurigel") {
		return Feurigel(level);
	} else if (name == "karnimani") {
		return Karnimani(level);
	} else {
		return Endivie(level);
	}
}



