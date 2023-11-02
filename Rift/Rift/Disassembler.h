#pragma once

#include <Windows.h>

#include "Opcode.h"
#include "Logger.h"

class Disassembler
{
	public:
		Disassembler();
		~Disassembler();

		size_t GetInstruction(LPVOID, int);

	private:
		std::vector<Opcode> memory;
		std::map<int, Opcode> instructions = {
			{ 0x1, Opcode("ADD", {}, 2) },
			{ 0x29, Opcode("SUB", {}, 2) },
			{ 0x74, Opcode("JE", {}, 2) },
			{ 0x80, Opcode("CMP", {}, 2) },
			{ 0x8D, Opcode("LEA", {}, 2) },
			{ 0x89, Opcode("MOV", {}, 2) },
			{ 0xE8, Opcode("CALL", {}, 2) }
		};
};