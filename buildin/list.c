#include <buildin/list.h>
#include <stdlib.h>
#include <assert.h>

struct list_node_t* __libc_list_create(uint64_t data, uint64_t data2, struct list_node_t* next) {
	struct list_node_t* new_node = __libc_malloc(sizeof(struct list_node_t));

	assert(new_node != NULL);

	new_node->data = data;
	new_node->data2 = data2;
	new_node->next = next;

	return new_node;
}

void __libc_list_traverse(struct list_node_t* head, __libc_list_callback f) {
	struct list_node_t* cursor = head;

	while(cursor != NULL) {
		f(cursor);
		cursor = cursor->next;
	}
}

struct list_node_t* __libc_list_append(uint64_t data, uint64_t data2, struct list_node_t* head) {
	struct list_node_t* cursor = head;
	struct list_node_t* tmp = NULL;

	while(cursor != NULL) {
		tmp = cursor;
		cursor = cursor->next;
	}

	struct list_node_t* new_node = __libc_list_create(data, data2, NULL);
	tmp->next = new_node;

	return head;
}

struct list_node_t* __libc_list_search(struct list_node_t* head, uint64_t data) {
	struct list_node_t* cursor = head;

	while(cursor != NULL) {
		if(cursor->data == data) {
			return cursor;
		}

		cursor = cursor->next;
	}

	return NULL;
}

struct list_node_t* __libc_list_remove_front(struct list_node_t* head) {
	if(head == NULL) {
		return NULL;
	}

	struct list_node_t* front = head;
	head = head->next;

	if(front == head) {
		head = NULL;
	}

	__libc_free(front);

	return head;
}

struct list_node_t* __libc_list_remove_back(struct list_node_t* head) {
	if(head->next == NULL || head == NULL) {
		return NULL;
	}

	struct list_node_t* current = head;

	while (current->next->next != NULL) {
		current = current->next;
	}
	
	__libc_free(current->next);

	current->next = NULL;

	return head;
}

struct list_node_t* __libc_list_remove(struct list_node_t* head, struct list_node_t* nd) {
	if(nd == head) {
		head = __libc_list_remove_front(head);
		return head;
	}

	if(nd->next == NULL) {
		head = __libc_list_remove_back(head);
		return head;
	}

	struct list_node_t* cursor = head;

	while(cursor != NULL) {
		if(cursor->next == nd) {
			break;
		}

		cursor = cursor->next;
	}

	if(cursor != NULL) {
		struct list_node_t* tmp = cursor->next;
		cursor->next = tmp->next;
		tmp->next = NULL;
		__libc_free(tmp);
	}

	return head;
}

void __libc_list_dispose(struct list_node_t* head) {
	struct list_node_t* cursor;
	struct list_node_t* tmp;

	if(head != NULL) {
		cursor = head->next;
		head->next = NULL;
		while(cursor != NULL) {
			tmp = cursor->next;
			__libc_free(cursor);
			cursor = tmp;
		}
	}
}