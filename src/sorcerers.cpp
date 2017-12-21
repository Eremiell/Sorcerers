#include <iostream>
#include <exception>
#include <nlohmann/json.hpp>
#include "inc/game.hpp"

int main(int argc, char **argv) {
	try {
		if (argc > 1) {
			sorcerers::Game g(argv[1]);
			g.play();
		}
		else {
			sorcerers::Game g;
			g.play();
		}
	}
	catch (std::string e) {
		std::cout << e << '\n';
		return 1;
	}
	catch (nlohmann::detail::exception e) {
		std::cout << "JSON parsing error!\n" << e.what() << '\n';
		return 2;
	}
	catch (std::exception e) {
		std::cout << "PRG error!\n" << e.what() << '\n';
		return 3;
	}
	return 0;
}
