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

#ifdef __cplusplus
#pragma once

#include <string.h>
#include <stdlib.h>

template <typename T>
class list {
	public:

		struct node {
			T data;
			bool taken = false;
		};

		list(int initial_length) {
			length = initial_length;
			data = (node*) malloc((length + 1) * sizeof(node));
			memset(data, 0, (length + 1) * sizeof(node));
		};

		~list() {
			free(data);
		}

		template <typename Y>
		node* find(bool (*f)(Y, node*), Y arg) {
			for (size_t i = 0; i < length; i++) {
				if (data[i].taken) {
					if (f(arg, &data[i])) {
						return &data[i];
					}
				}
			}
			
			return nullptr;
		}

		template <typename Y>
		void foreach(void (*f)(Y, node*), Y arg) {
			for (int i = 0; i < length; i++) {
				if (data[i].taken) {
					f(arg, &data[i]);
				}
			}
		}

		void remove(node* n) {
			for (size_t i = 0; i < length; i++) {
				if (&data[i] == n) {
					memset(&data[i], 0, sizeof(node));
				}
			}
		}

		node* add(T d) {
		retry:
			for (int i = 0; i < length; i++) {
				if (!data[i].taken) {
					data[i].data = d;
					data[i].taken = true;
					return &data[i];
				}
			}

			data = (node*) realloc(data, (length + 2) * sizeof(node));
			memset(&data[length], 0, sizeof(node));
			length++;
			goto retry;
		}
	
		int length;
		node* data;
};
#endif