#pragma once

#include <stdbool.h>

bool Base64EncodeW(WCHAR **dest, unsigned long *dlen, const unsigned char *src, unsigned long slen);
bool Base64EncodeA(char **dest, unsigned long *dlen, const unsigned char *src, unsigned long slen);

bool Base64DecodeW(unsigned char **dest, unsigned long *dlen, const WCHAR *src, unsigned long slen);
bool Base64DecodeA(unsigned char **dest, unsigned long *dlen, const char *src, unsigned long slen);
