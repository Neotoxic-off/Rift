#include "Disassembler.h"

Disassembler::Disassembler()
{
	memory = std::vector<Opcode>();
}

Disassembler::~Disassembler()
{

}

size_t Disassembler::Add(LPVOID address, int byte)
{
	auto instruction = instructions.find(byte);
	std::string log;

	if (instruction != instructions.end())
	{
		log = std::format("{} | {}", address, instruction->second.instruction);
	}
	else {
		log = std::format("{} | 0x{:x}", address, byte);
	}

	std::cout << log << std::endl;

	return (0);
}