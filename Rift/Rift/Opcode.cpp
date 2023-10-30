#include "Opcode.h"

Opcode::Opcode(std::string instruction, std::vector<std::string> arguments, size_t padding)
{
	this->instruction = instruction;
	this->arguments = arguments;
	this->padding = padding;
}

Opcode::~Opcode()
{

}
