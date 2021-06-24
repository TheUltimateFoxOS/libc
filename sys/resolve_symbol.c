#include <sys/resolve_symbol.h>
#include <stddef.h>

void* resolve_symbol(char* name) {
	void* symbol = NULL;
	__asm__ __volatile__ ("int $0x30" : "=c" (symbol) : "a" (SYS_RESOLVE_SYMBOL), "b" (name));

	return symbol;
}