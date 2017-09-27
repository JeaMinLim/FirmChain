#include <stdio.h>
#include <string.h>
#include <sys/queue.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#define MAX_NODE_ 7
const int MAX_NODE = 7;
const int VICTIM_NODE = 0;

struct node *INFO;
struct block *block_ptr;
struct node *DEVICE_info[MAX_NODE_];

struct block_v1 {
	// Header Start //
	struct block *ptr;
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

struct node {
	char name[20];
	char model_name[4];
	char firmware_version[4];
	char verifier[32];
	int versioncheck_request;
};

struct manager {
	char name[20];
	int versioncheck_request;
};