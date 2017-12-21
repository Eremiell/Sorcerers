#include "inc/state.hpp"
#include <sstream>

namespace sorcerers {
	State::State() : start(false), end(false), text(""), prg(false), dice(0), raw_prg(false), dice_type(0), modifier(0) {}

	void State::set_text(std::string text) {
		this->text = text;
		return;
	}

	void State::add_goto(std::string label, std::string address) {
		this->gotos.emplace(label, address);
		return;
	}

	void State::set_start(bool start) {
		this->start = start;
		return;
	}

	void State::set_end(bool end) {
		this->end = end;
		return;
	}

	void State::set_prg(std::string prg) {
		std::istringstream iss(prg);
		iss >> this->dice;
		char raw;
		iss >> raw;
		switch (raw) {
			case 'r':
				this->raw_prg = true;
				break;
			case 'd':
			default:
				this->raw_prg = false;
				break;
		}
		iss >> this->dice_type;
		if (iss.good()) {
			iss >> this->modifier;
		}
		if (iss.fail() || iss.bad()) {
			throw std::string("Wrong prg format: " + prg);
		}
		this->dist.param(std::uniform_int_distribution<std::int64_t>::param_type(this->raw_prg?0:1, this->raw_prg?dice_type-1:dice_type));
		this->prg = true;
		return;
	}

	bool State::get_start() {
		return this->start;
	}

	bool State::get_end() {
		return this->end;
	}

	bool State::has_prg() {
		return this->prg;
	}

	std::uniform_int_distribution<std::int64_t>& State::get_dist() {
		return this->dist;
	}

	const std::string& State::get_text() const {
		return this->text;
	}

	const std::unordered_map<std::string, std::string>& State::get_gotos() const {
		return this->gotos;
	}
}
