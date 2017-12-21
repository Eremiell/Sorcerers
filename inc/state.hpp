#pragma once
#ifndef STATE_HPP
#define STATE_HPP

#include <string>
#include <unordered_map>
#include <random>

namespace sorcerers {
	class State {
		public:
			State();
			void set_text(std::string text);
			void add_goto(std::string label, std::string address);
			void set_start(bool start = true);
			void set_end(bool end = true);
			void set_prg(std::string prg);
			bool get_start();
			bool get_end();
			bool has_prg();
			std::uniform_int_distribution<std::int64_t>& get_dist();
			const std::string& get_text() const;
			const std::unordered_map<std::string, std::string>& get_gotos() const;
		private:
			bool start;
			bool end;
			std::string text;
			bool prg;
			std::size_t dice;
			bool raw_prg;
			std::size_t dice_type;
			std::int64_t modifier;
			std::unordered_map<std::string, std::string> gotos;
			std::uniform_int_distribution<std::int64_t> dist;
	};
}

#endif
