#pragma once
#include <stdbool.h>

bool CryptoInit(HCRYPTKEY *key, HCRYPTPROV *provider, unsigned char **publicKey, unsigned char **privateKey);
bool Encrypt(HCRYPTKEY key, char **cipherText, unsigned long *cLen, unsigned char *plainText, unsigned long pLen);
bool Decrypt(HCRYPTKEY key, unsigned char **plainText, char *cipherText, unsigned long cLen);
void CryptoUninit(HCRYPTKEY key, HCRYPTPROV provider);