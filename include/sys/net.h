#pragma once

#include <extern.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

union ip_u {
	uint8_t ip_p[4];
	uint32_t ip;
};

EXPOSEC union ip_u dns_resolve(const char* domain, int nic_id);
EXPOSEC bool icmp_echo_request(uint32_t ip, int nic_id);

enum socket_type {
	TCP_SOCKET,
	UDP_SOCKET
};

EXPOSEC int connect(uint32_t ip, uint16_t port, int socket_type);
EXPOSEC void disconnect(int socket);

EXPOSEC int send(int socket, const void* data, size_t size);
EXPOSEC int recv(int socket, void* data, size_t size);