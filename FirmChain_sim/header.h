#include <stdio.h>
#include <string.h>
#include <sys/queue.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "sha256.h"

#define MAX_NODE_ 7
const int MAX_NODE = MAX_NODE_;
#define MAX_MANAGER_ 3
const int MAX_MANAGER = MAX_MANAGER_;
const int VICTIM_NODE = 0;

struct node *NODE_INFO;
struct manager *MANAGER_INFO;
struct block_v1 *block_ptr;
struct hashchain *hash_ptr;
struct node *NODE_info[MAX_NODE_];
struct manager *MANAGER_info[MAX_MANAGER_];

struct block_v1 {
	// Header Start //
	struct block_v1 *ptr;
	float size;	
	int version;
	char prev_hash[32];
	time_t time;
	int difficalty;
	int nonce;
	int type;
	// Header end //
	char model[4];
	int firmware_version;
	char verifier[32];
} *GENESIS;

struct hashchain {
	BYTE hash[SHA256_BLOCK_SIZE];
	struct hashchain *_ptr;
} *GENESIS_HASH;

struct node {
	char name[20];
	char model_name[4];
	char firmware_version[4];
	char verifier[32];
	int manager_num;
};

struct manager {
	char name[20];
	int request_flag[2];
};