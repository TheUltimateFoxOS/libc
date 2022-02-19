#pragma once

#include <extern.h>
#include <stdint.h>
#include <stdbool.h>

union ip_u {
	uint8_t ip_p[4];
	uint32_t ip;
};

EXPOSEC union ip_u dns_resolve(const char* domain, int nic_id);
EXPOSEC bool icmp_echo_request(uint32_t ip, int nic_id);