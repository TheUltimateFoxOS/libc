#pragma once

#define NULL ((void*) 0)

typedef __SIZE_TYPE__ size_t;
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#ifndef __cplusplus
typedef __WCHAR_TYPE__ wchar_t;
#endif

#define offsetof(TYPE, MEMBER)	__builtin_offsetof (TYPE, MEMBER)
