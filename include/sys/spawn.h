#pragma once
#include <extern.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct s_registers {
	uint64_t cr4;
	uint64_t cr3;
	uint64_t cr2;
	uint64_t cr0;
	uint64_t r15;
	uint64_t r14;
	uint64_t r13;
	uint64_t r12;
	uint64_t r11;
	uint64_t r10;
	uint64_t r9;
	uint64_t r8;
	uint64_t rdi;
	uint64_t rsi;
	uint64_t rbp;
	uint64_t rbx;
	uint64_t rdx;
	uint64_t rcx;
	uint64_t rax;
	uint64_t interrupt_number;
	uint64_t error_code;
	uint64_t rip;
	uint64_t cs;
	uint64_t rflags;
	uint64_t rsp;
} __attribute__((packed)) s_registers;

typedef void (*signal_handler)(uint8_t signum);

typedef struct task {
	s_registers regs;
	char fxsr_state[512] __attribute__((aligned(16)));
	uint64_t stack;

	bool first_sched; // is true if the task just got created
	bool kill_me; // if true task gets killed
	bool lock; // if true task is locked and doesent get scheduled

	bool is_elf; // if true task is started from an elf
	char** argv;
	char** envp;

	void* offset; // offset of the elf
	int page_count; // number of pages the elf needs
} task;

EXPOSEC task* spawn(const char* path, const char* argv[], const char* envp[]);