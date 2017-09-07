#include <stdio.h>

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
};

struct node {
	char name[20];
	char model_name[4];
	int firmware_version;
	char verifier[32]; 
};
