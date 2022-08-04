#include <buildin/sighandler.h>
#include <stdio.h>
#include <stdlib.h>

char* __libc_get_exception_name(int exc){
	switch(exc){
		case 0x0:
			return("Divide by Zero");
			break;
		case 0x1:
			return("Debug");
			break;
		case 0x2:
			return("Non Maskable Interrupt");
			break;
		case 0x3:
			return("Breakpoint");
			break;
		case 0x4:
			return("Overflow");
			break;
		case 0x5:
			return("Bound Range");
			break;
		case 0x6:
			return("Invalid Opcode");
			break;
		case 0x7:
			return("Device Not Available");
			break;
		case 0x8:
			return("Double Fault");
			break;
		case 0x9:
			return("Coprocessor Segment Overrun");
			break;
		case 0xa:
			return("Invalid TSS");
			break;
		case 0xb:
			return("Segment not Present");
			break;
		case 0xc:
			return("Stack Fault");
			break;
		case 0xd:
			return("General Protection");
			break;
		case 0xe:
			return("Page Fault");
			break;
		case 0x10:
			return("x87 Floating Point");
			break;
		case 0x11:
			return("Alignment Check");
			break;
		case 0x12:
			return("Machine Check");
			break;
		case 0x13:
			return("SIMD Floating Point");
			break;
		case 0x1e:
			return("Security-sensitive event in Host");
			break;
		default:
			return("Reserved");
			break;
	}
}

void __libc_sighandler(uint8_t signum) {
	printf("\n\nSignal: %s\n", __libc_get_exception_name(signum));

	abort();
}


void __libc_intr_sighandler(uint8_t signum) {
	printf("Force exiting...\n");
	abort();
}