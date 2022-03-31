#include <sys/sound_push_note.h>
#include <sys/get_syscall_id.h>

int sys_sound_push_id = -1;

void sound_push_note(uint8_t note, uint8_t channel, uint16_t duration_ms) {
	if (sys_sound_push_id == -1) {
		sys_sound_push_id = get_syscall_id("sys_sound_push_note");
	}

	__asm__ __volatile__ ("int $0x30" :: "a" (sys_sound_push_id), "b" (note), "c" (channel), "d" (duration_ms));
}