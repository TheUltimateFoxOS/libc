#include <stdlib.h>
#include <sys/memory.h>
#include <buildin/list.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>	

struct list_node_t* alloc_list_head = NULL;

void __libc_init_alloc() {
	alloc_list_head = __libc_list_create(START_MARKER, START_MARKER, NULL);
}

void __libc_dealloc_enumerator(struct list_node_t* node) {
	// printf("Dealloc: 0x%x, size: 0x%x\n", node->data, node->data2);

	if(node->data != START_MARKER) {
	#ifdef MEMORY_TRACKING
		printf("--- WARNING --- leaking memory at 0x%x\n", node->data);
	#endif
		__libc_free((void*) node->data, node->data2);
	}
}

void __libc_uninit_alloc() {
	__libc_list_traverse(alloc_list_head, __libc_dealloc_enumerator);
	__libc_list_dispose(alloc_list_head);
}

// TODO allow sizes bigger than 4096
// This needs to store somewhere the size of the allocated memory

void* __libc_malloc(size_t size) {
	// assert(size < 0x1000);
	return memory(NULL, size, MEM_ALLOC);
}

void __libc_free(void* address, size_t size) {
	memory(address, size, MEM_FREE);
}

void* malloc(size_t size) {
	void* ptr = __libc_malloc(size);
	__libc_list_append((uint64_t) ptr, size, alloc_list_head);

	return ptr;
}

void* calloc(size_t count, size_t size) {
	void* addr = malloc(count * size);
	memset(addr, 0, count * size);
	return addr;
}

void* realloc(void* pointer, size_t size) {
	if (pointer == NULL) {
		return malloc(size);
	}

	void* new_ptr = malloc(size);

	struct list_node_t* old_alloc = __libc_list_search(alloc_list_head, (uint64_t) pointer);

	if(old_alloc->data2 > size) {
		memcpy(new_ptr, pointer, size);
	} else {
		memcpy(new_ptr, pointer, old_alloc->data2);
	}

	free(pointer);

	return new_ptr;
}

void free(void* addr) {
	struct list_node_t* node = __libc_list_search(alloc_list_head, (uint64_t) addr);
	__libc_free(addr, node->data2);
	alloc_list_head = __libc_list_remove(alloc_list_head, node);
}