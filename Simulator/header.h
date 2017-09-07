#include <stdio.h>
#include <string.h>
#include <sys/queue.h>
#include <stdlib.h>
#include <pthread.h>

const int MAX_NODE=7;

struct block {
	// Header Start //
	float size;	
	int version;
	char prev_hash[32];
	int merkle_root[8];
	// Header end //
	int verification_count;
	char merkle_tree[4];
	char verification_log[4];
	char model[4];
	int firmware_version;
	char verifier[32];
	SLIST_ENTRY(block) blocks;
} *GENESIS;

struct node {
	char name[20];
	char model_name[4];
	char firmware_version[4];
	char verifier[32]; 
};
