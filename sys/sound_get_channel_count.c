#include <sys/sound_get_channel_count.h>
#include <sys/get_syscall_id.h>

int sys_sound_get_channel_count_id = -1;

int sound_get_channel_count() {
	if (sys_sound_get_channel_count_id == -1) {
		sys_sound_get_channel_count_id = get_syscall_id("sys_sound_get_channel_count");
	}

	__asm__ __volatile__ ("int $0x30" : "=b" (sys_sound_get_channel_count_id));

	return sys_sound_get_channel_count_id;
}