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
const int VICTIM_NODE = 6;

struct node *INFO;
struct block *block_ptr;
struct node *DEVICE_info[MAX_NODE_];

struct block {
	// Header Start //
	struct block *ptr;
	float size;	
	int version;
	char prev_hash[32];
	int merkle_root[8];
	// Header end //
	int verification_count;
	char merkle_tree[4];
	// verification log //
	// timestemp, requester`s ID, responser`s ID, 
	// verification_log[0] = timestemp
	// verification_log[1] = requester`s ID
	// verification_log[2] = responser`s ID
	unsigned int verification_log[3];
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
