#include <buildin/thread.h>
#include <buildin/list.h>

#include <stddef.h>

struct list_node_t* child_list_head = NULL;


void __libc_kill_childs_enumerator(struct list_node_t* node) {
	// printf("Kill: 0x%x, already_exit: 0x%x\n", node->data, node->data2);

	if(node->data != START_MARKER) {
		task_t* t = (task_t*) node->data;
		if (!node->data2) {
			t->kill_me = true;
		}
	}
}


EXPOSEC void __libc_kill_childs(void) {
	__libc_list_traverse(child_list_head, __libc_kill_childs_enumerator);
}

EXPOSEC void __libc_init_childs_list(void) {
	child_list_head = __libc_list_create(START_MARKER, START_MARKER, NULL);
}

EXPOSEC task_t* create_thread(void* entry) {
	task_t* t = thread(entry, true);

	__libc_list_append((uint64_t) t, 0, child_list_head);
	struct list_node_t* node = __libc_list_search(child_list_head, (uint64_t) t);

	t->on_exit = &node->data2;

	return t;
}