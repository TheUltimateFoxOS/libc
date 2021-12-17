#pragma once

#define NULL ((void*) 0)

typedef __SIZE_TYPE__ size_t;

#define offsetof(TYPE, MEMBER)	__builtin_offsetof (TYPE, MEMBER)
