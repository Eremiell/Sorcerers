#include "inc/game.hpp"
#include <iostream>
#include <chrono>
#include <fstream>
#include <nlohmann/json.hpp>

namespace sorcerers {
	Game::Game() : start("^start"), at(this->start), mt(std::chrono::high_resolution_clock::now().time_since_epoch().count()) {
		this->states.emplace("^start", State{});
		this->states["^start"].set_text("start");
		this->states["^start"].add_goto("next", "next");
		this->states["^start"].add_goto("loop", "^start");
		this->states["^start"].set_start();
		this->states.emplace("next", State{});
		this->states["next"].set_text("next");
		this->states["next"].add_goto("moonwalk", "^start");
		this->states["next"].add_goto("loop", "next");
		this->states["next"].add_goto("win", "$victory");
		this->states["next"].add_goto("lose", "$failure");
		this->states.emplace("$victory", State{});
		this->states["$victory"].set_text("you won");
		this->states["$victory"].add_goto("sweet", "");
		this->states["$victory"].set_end();
		this->states.emplace("$failure", State{});
		this->states["$failure"].set_text("you lost");
		this->states["$failure"].add_goto("boo", "");
		this->states["$failure"].set_end();
	}

	Game::Game(std::string filename) : start("^start"), at(this->start), mt(std::chrono::high_resolution_clock::now().time_since_epoch().count()) {
		std::ifstream file(filename);
		if (!file.good()) {
			throw std::string("Wrong filename!");
		}
		nlohmann::json game;
		file >> game;
		for (auto it = game.begin(); it != game.end(); ++it) {
			this->states.emplace(it.key(), State{});
			this->states[it.key()].set_text(it.value()["text"]);
			if (!it.value().count("gotos") || it.value()["gotos"].empty()) {
				throw std::string("No gotos for state " + it.key() + "!");
			}
			for (auto goto_it = it.value()["gotos"].begin(); goto_it != it.value()["gotos"].end(); ++goto_it) {
				this->states[it.key()].add_goto(goto_it.key(), goto_it.value());
			}
			if (it.value().count("start")) {
				this->states[it.key()].set_start(it.value()["start"]);
			}
			if (it.value().count("end")) {
				this->states[it.key()].set_start(it.value()["end"]);
			}
			if (it.value().count("prg")) {
				this->states[it.key()].set_prg(it.value()["prg"]);
			}
		}
	}

	void Game::play() {
		while (this->at != "") {
			std::cout /*<< this->at << '\n'*/ << this->states[this->at].get_text() << '\n';
			if (this->states[this->at].has_prg()) {
				std::int64_t rolled = this->states[this->at].get_dist()(this->mt);
				this->at = this->states[this->at].get_gotos().at("@" + std::to_string(rolled));
			}
			else {
				std::cout << "Options: ";
				for (auto &gt : this->states[this->at].get_gotos()) {
					std::cout << gt.first << '\t';
				}
				std::cout << '\n';
				std::string next;
				std::getline(std::cin, next);
				if (this->states[this->at].get_gotos().count(next)) {
					this->at = this->states[this->at].get_gotos().at(next);
				}
			}
		}
		return;
	}
}
