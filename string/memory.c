#include <string.h>

#ifndef FAST_MEM
void* memcpy(void* dest, const void* src, size_t n) {
	unsigned char* d = (unsigned char*) dest;
	const unsigned char* s = (unsigned char*) src;

	while (n--) {
		*d++ = *s++;
	}

	return dest;
}

void* memset(void* start, uint8_t value, uint64_t num) {
	for (uint64_t i = 0; i < num; i++){
		*(uint8_t*)((uint64_t)start + i) = value;
	}

	return start;
}

#else

__attribute__((naked)) void* memcpy(void* dest, const void* src, size_t n) {
	__asm__ __volatile__ (	"movq %rdi, %rax;"
							"movq %rdx, %rcx;"
							"shrq $3, %rcx;"
							"andl $7, %edx;"
							"rep movsq;"
							"movl %edx, %ecx;"
							"rep movsb;"
							"ret;");
}

__attribute__((naked)) void* memset(void* start, uint8_t value, uint64_t num) {
	__asm__ __volatile__ (	"movq %rdi, %r9;"
							"movq %rdx, %rcx;"
							"andl $7, %edx;"
							"shrq $3, %rcx;"
							"movzbl %sil, %esi;"
							"movabs $0x0101010101010101, %rax;"
							"imulq %rsi, %rax;"
							"rep stosq;"
							"movl %edx, %ecx;"
							"rep stosb;"
							"movq %r9, %rax;"
							"ret;");
}
#endif

int memcmp(const void * _s1, const void* _s2, size_t n) {

	const unsigned char* s1 = (unsigned char*) _s1;
	const unsigned char* s2 = (unsigned char*) _s2;

	while(n--) {
		if(*s1 != *s2) {
			return *s1 - *s2;
		}
		++s1;
		++s2;
	}
	return 0;
}