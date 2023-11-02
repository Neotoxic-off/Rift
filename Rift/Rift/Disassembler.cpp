#include "Disassembler.h"

Disassembler::Disassembler()
{
	memory = std::vector<Opcode>();
}

Disassembler::~Disassembler()
{
	memory.clear();
}

size_t Disassembler::GetInstruction(LPVOID address, int byte)
{
	auto instruction = instructions.find(byte);
	std::string log;

	if (instruction != instructions.end())
	{
		memory.push_back(instruction->second);
		log = std::format("{} | {}", address, instruction->second.instruction);
	}
	else
	{
		log = std::format("{} | 0x{:x}", address, byte);
	}

	std::cout << log << std::endl;

	return (0);
}