#pragma once

#include <vector>
#include <map>
#include <iostream>

class Opcode
{
	public:
		Opcode(std::string, std::vector<std::string>, size_t);
		~Opcode();

		std::string instruction;
		std::vector<std::string> arguments;
		size_t padding;
};
