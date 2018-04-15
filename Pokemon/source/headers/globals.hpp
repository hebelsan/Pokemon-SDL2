/*
 * global.hpp
 * global parameter
 */

#ifndef GLOBALS_HPP_
#define GLOBALS_HPP_

namespace globals {
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	const float SPRITE_SCALE = 2.0f;
}

namespace sides {
	enum Side {
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		NONE
	};

	inline Side getOppositeSide(Side side) {
		return
				side == TOP ? BOTTOM :
				side == BOTTOM ? TOP :
				side == LEFT ? RIGHT :
				side == RIGHT ? LEFT :
				NONE;
	}
}

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum PokemonExpTyp {
	SCHNELL,
	MITTEL_SCHNELL,
	MITTEL_LANGSAM,
	LANGSAM,
	ERRATIC,
	FLUCTUATING,
	UNKNOWN
};

enum PokemonTyp {
	NORMAL,
	KAMPF,
	FLUG,
	GIFT,
	BODEN,
	GESTEIN,
	KAEFER,
	GEIST,
	STAHL,
	FEUER,
	WASSER,
	PFLANZE,
	ELEKTRO,
	PSYCHO,
	EIS,
	DRACHE,
	UNLICHT,
	UNKNOWNTYPE
};

enum SchadensKlasse {
	PHYSISCH,
	SPEZIAL,
	STATUS,
	UNKNOWNCLASS
};

enum MenuItem {
	POKEDEX,
	POKEMON,
	BAG,
	POKECOM,
	ASH,
	SAVE,
	OPTION,
	BACK
};

struct Vector2 {
	int x, y;
	Vector2() :
		x(0), y(0)
	{}
	Vector2(int x, int y) :
		x(x), y(y)
	{}
	Vector2 zero() {
		return Vector2(0, 0);
	}
};

#endif /* GLOBALS_HPP_ */
