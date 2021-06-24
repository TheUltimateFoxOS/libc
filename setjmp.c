#include <setjmp.h>

__attribute__((naked)) void longjmp(jmp_buf state, int value) {
	__asm__ __volatile__ (	"movq  %rsi, %rax;"
							"testq %rax, %rax;"
							"setz  %al;"
							"movq  0(%rdi),  %rbx;"
							"movq  8(%rdi),  %rbp;"
							"movq  16(%rdi), %r12;"
							"movq  24(%rdi), %r13;"
							"movq  32(%rdi), %r14;"
							"movq  40(%rdi), %r15;"
							"movq  48(%rdi), %rsp;"
							"jmp  *56(%rdi);");
}

__attribute__((naked)) int setjmp(jmp_buf state) {
	__asm__ __volatile__ (	"movq %rbx, 0(%rdi);"
							"movq %rbp, 8(%rdi);"
							"movq %r12, 16(%rdi);"
							"movq %r13, 24(%rdi);"
							"movq %r14, 32(%rdi);"
							"movq %r15, 40(%rdi);"
							"leaq 8(%rsp), %rdx;"
							"movq %rdx, 48(%rdi);"
							"movq (%rsp), %rdx;"
							"movq %rdx, 56(%rdi);"
							"movq $0, %rax;"
							"ret;");
}