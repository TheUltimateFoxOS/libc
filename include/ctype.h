#pragma once

#define isspace(c) (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
#define isdigit(c) (c >= '0' && c <= '9')
#define isupper(c) (c >= 'A' && c <= 'Z')
#define islower(c) (c >= 'a' && c <= 'z')
#define iscntrl(c) ((c >= 0x00 && c <= 0x1F) || (c == 0x7F))
#define isalpha(c) (islower(c) || isupper(c))
#define isalnum(c) (isalpha(c) || isdigit(c))
#define isblank(c) (c == ' ' || c == '\t')
#define isxdigit(c) (isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))

#define tolower(c) (isupper(c) ? c - ('A' - 'a') : c)
#define toupper(c) (islower(c) ? c - ('a' - 'A') : c)