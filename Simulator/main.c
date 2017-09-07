#include "header.h"

int main() {
	printf("Start test\n");
	printf(" : creating GENESIS Block \n");
	// creating genesis block //
	struct block GENESIS;
	GENESIS.version	= 0.1;
	GENESIS.prev_hash[0] = '\0';
	GENESIS.merkle_root[0] = 0;
	GENESIS.verification_count = 0;
	GENESIS.merkle_tree[0] = '\0';
	GENESIS.verification_log[0] = '\0';
	GENESIS.model[0] = '\0';
	GENESIS.firmware_version = 0;
	GENESIS.verifier[0] = '\0';
	printf(" : Genesis Block is ready \n");

	// create 6 nodes //
	struct node DEVICE[6];
	DEVICE[0].
	DEVICE[1]
	DEVICE[2]
	DEVICE[3]
	DEVICE[4]
	DEVICE[5]

		

	return 0;
}


