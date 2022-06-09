 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "des.h"

static FILE *key_file, *input_file, *output_file;

#define ACTION_GENERATE_KEY "-g"
#define ACTION_ENCRYPT "-e"
#define ACTION_DECRYPT "-d"

// DES key is 8 bytes long
#define DES_KEY_SIZE 8

void Des_En(char *data_block,char *des_key,char *processed_block)
{
	key_set* key_sets = (key_set*)malloc(17 * sizeof(key_set));

	process_message(data_block, processed_block, key_sets,1);
	memset(data_block, 0, 8);
	free(key_sets);
}

void Des_De(char *data_block, char *des_key, char *processed_block)
{
	key_set* key_sets = (key_set*)malloc(17 * sizeof(key_set));
	process_message(data_block, processed_block, key_sets, 0);
	memset(data_block, 0, 8);
	free(key_sets);
}
