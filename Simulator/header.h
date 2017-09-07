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
	int model;
	int firmware_version;
	char verifier[32];
};

