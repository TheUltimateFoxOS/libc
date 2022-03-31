#include <sys/sound_sync.h>
#include <sys/get_syscall_id.h>

int sys_sound_sync_id = -1;

void sound_sync() {
	if (sys_sound_sync_id == -1) {
		sys_sound_sync_id = get_syscall_id("sys_sound_sync");
	}

	__asm__ __volatile__ ("int $0x30" :: "a" (sys_sound_sync_id));
}