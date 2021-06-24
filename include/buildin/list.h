#pragma once
#include <extern.h>
#include <stdint.h>

struct list_node_t {
	uint64_t data;
	uint64_t data2;
	struct list_node_t* next;
};

typedef void (*__libc_list_callback)(struct list_node_t* node);

EXPOSEC struct list_node_t* __libc_list_create(uint64_t data, uint64_t data2, struct list_node_t* next);
EXPOSEC void __libc_list_traverse(struct list_node_t* head, __libc_list_callback f);
EXPOSEC struct list_node_t* __libc_list_append(uint64_t data, uint64_t data2, struct list_node_t* head);
EXPOSEC struct list_node_t* __libc_list_search(struct list_node_t* head, uint64_t data);
EXPOSEC struct list_node_t* __libc_list_remove_front(struct list_node_t* head);
EXPOSEC struct list_node_t* __libc_list_remove_back(struct list_node_t* head);
EXPOSEC struct list_node_t* __libc_list_remove(struct list_node_t* head, struct list_node_t* nd);
EXPOSEC void __libc_list_dispose(struct list_node_t* head);
