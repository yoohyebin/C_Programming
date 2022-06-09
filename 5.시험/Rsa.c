#include <stdio.h>
#include <Windows.h>
#include <io.h>
#include <conio.h>
#include "rsa2048.h"
#include "base64.h"
#include "common.h"

void rsa()
{
	struct _finddata_t fd;
	struct _finddata_t fd1;
	long handle;
	HCRYPTPROV hCryptProv = 0;
	HCRYPTKEY key = 0;
	unsigned long cLen = 0;
	unsigned char *cipherText = (unsigned char*)malloc(344 * sizeof(char));
	unsigned char *plainText = (unsigned char*)malloc(8 * sizeof(char));
	unsigned char *decrypted = (unsigned char*)malloc(8 * sizeof(char));
	unsigned char *publicKey = 0;
	unsigned char *privateKey = 0;
	char str[260] = "", filename[260] = "";
	int result = 1, len = 0, i;

	FILE *en_file = fopen("title.txt", "rb");
	FILE *en_file1 = fopen("title.txt", "rb");


	if (!CryptoInit(&key, &hCryptProv, &publicKey, &privateKey))
	{
		printf("Crypto initializing failed\n");
		return EXIT_FAILURE;
	}

	handle = _findfirst(".\\RSA\\ori\\*.*", &fd);
	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}

	while (result != -1)
	{
		sprintf(filename, ".\\RSA\\ori\\%s", fd.name);
		FILE *input_file = fopen(filename, "rb");
		if (input_file == NULL)
		{
			result = _findnext(handle, &fd);
			continue;
		}
		sprintf(str, ".\\RSA\\en\\en_%s", fd.name);
		FILE *output_file = fopen(str, "wb");
		if (fd.size != 0)
		{
			while (fread(plainText, 1, 8, en_file))
			{
				fwrite(plainText, 1, 8, output_file);
				memset(plainText, 0, 8);
			}
			while (fread(plainText, 1, 8, input_file))
			{
				if (!Encrypt(key, &cipherText, &cLen, (unsigned char *)plainText, strlen(plainText)))
				{
					printf("Encryption failed\n");
					if (hCryptProv) CryptReleaseContext(hCryptProv, 0);
					return EXIT_FAILURE;
				}
				printf("plainText:%s \n", plainText);
				printf("cipherText:%s\n", cipherText);
				fwrite(cipherText, 1, cLen, output_file);
			}
		}
		rewind(en_file);
		fclose(input_file);
		fclose(output_file);
		result = _findnext(handle, &fd);
	}
	_findclose(handle);
	fclose(en_file);
	result = 1;

	handle = _findfirst(".\\RSA\\en\\en*.*", &fd1);
	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}
	while (result != -1)
	{
		sprintf(filename, ".\\RSA\\en\\%s", fd1.name);
		FILE *input_file1 = fopen(filename, "rb");
		if (input_file1 == NULL)
		{
			result = _findnext(handle, &fd1);
			continue;
		}
		strcpy(str, fd1.name);
		len = strlen(str);
		for (i = 3; i < len; i++)
			str[i - 3] = str[i];
		str[len - 3] = '\0';
		sprintf(filename, ".\\RSA\\de\\de_%s", str);
		FILE *output_file1 = fopen(filename, "wb");

		if (fd1.size != 0)
		{
			while (fread(cipherText, 1, 8, en_file1))
			{
				fread(cipherText, 1, 8, input_file1);
				memset(cipherText, 0, 8);
			}
			while (fread(cipherText, 1, cLen, input_file1))
			{
				if (!Decrypt(key, &decrypted, cipherText, cLen))
				{
					printf("Decryption failed\n");
					SAFE_FREE(cipherText);
					if (hCryptProv) CryptReleaseContext(hCryptProv, 0);
					return EXIT_FAILURE;
				}
				printf("cipherText:%s\n", cipherText);
				printf("decrypted:%s\n", decrypted);
				fwrite(decrypted, 1, 8, output_file1);
			}
		}
		rewind(en_file1);
		fclose(input_file1);
		fclose(output_file1);
		result = _findnext(handle, &fd1);
	}

	SAFE_FREE(cipherText);
	SAFE_FREE(decrypted);

	CryptoUninit(key, hCryptProv);

	SAFE_FREE(publicKey);
	SAFE_FREE(privateKey);

	return EXIT_SUCCESS;
}
