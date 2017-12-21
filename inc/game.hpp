#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <unordered_map>
#include <random>
#include "inc/state.hpp"

namespace sorcerers {
	class Game {
		public:
			Game();
			Game(std::string filename);
			void play();
		private:
			std::string start;
			std::string at;
			std::mt19937_64 mt;
			std::unordered_map<std::string, State> states;
	};
}

#endif
